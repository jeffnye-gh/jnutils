//#include "types.h"
#include "ooo_cpu.h"
#include "tage.h"
#include "loop_pred.h"
#include <boost/algorithm/string.hpp>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <map>

extern Tage     tage_predictor[NUM_CPUS];
extern LoopPred loop_predictor[NUM_CPUS];

O3_CPU ooo_cpu[NUM_CPUS];

using namespace std;
using namespace boost;

int tst_idx = 0;

//32 is required to show diff in pred_comp/alt_comp
#define MAXCOUNT 4096

struct FetchEntry
{
  FetchEntry() {}

  FetchEntry(uint64_t _pc,
             uint64_t _shift,
             uint32_t _enc,
             uint64_t _targ,
             uint32_t _path,
             uint32_t _tkn,
             uint32_t _mis=0)
    : pc(_pc),
      shift_pc(_shift),
      enc(_enc),
      target(_targ),
      taken(_tkn),
      path(_path),
      mispredicted(_mis)
  {}

  uint64_t pc{0};
  uint64_t shift_pc{0};
  uint32_t enc{0};
  uint64_t target{0};
  uint32_t taken{0};
  uint32_t path{0};
  uint32_t mispredicted{0};

};

vector<FetchEntry> fetch_buffer;
std::ostream *lp_os;
std::ostream *tg_os;

// -------------------------------------------------------------------
// -------------------------------------------------------------------
size_t add_to_fetch_buffer(FetchEntry &fe)
{
  size_t index = fetch_buffer.size();
  fetch_buffer.push_back(fe);
  return index;
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
int begin(O3_CPU &cpu,int maxCount,string trace_file)
{
  ifstream in(trace_file.c_str());

  if(!in.is_open()) {
    cout<<"-E: could not open hex file "<<trace_file<<endl;
    return 1;
  }

  string line;
  int lineNo = 0;
  int mispredicts = 0;
  bitset<64> exp_gh(0),exp_ph(0);

  while (std::getline(in,line)) {
    ++lineNo;
    if(!(lineNo % 100000)) std::cout << "line#: " << lineNo << std::endl;

    vector<string> vec;
    boost::split(vec,line,is_any_of(" "),token_compress_on);
    if(vec.size() < 2) {
      cout<<"-E: error parsing input at line "<<lineNo<<endl;
      return 1;
    }

    vector<string> nvec;
    boost::split(nvec,vec[1],is_any_of("_"),token_compress_on);
    if(nvec.size() < 4) {
      cout<<"-E: error parsing vec[1] at line "<<lineNo<<endl;
      return 1;
    }

    FetchEntry entry;
    entry.pc       = (uint64_t) std::stoull(nvec[0],nullptr,16);
    entry.shift_pc = (uint64_t) entry.pc >> PC_SHIFT;
    entry.enc      = (uint32_t) std::stoull(nvec[1],nullptr,16);
    entry.target   = (uint64_t) std::stoull(nvec[2],nullptr,16);
    entry.taken    = (uint32_t) (std::stoi(nvec[3],nullptr,16));
    entry.path     = (uint32_t) ((entry.pc >> PC_SHIFT)&0x1);

    size_t fetchIndex = add_to_fetch_buffer(entry);

    //(*tg_os)<<"-I: start pc 0x"<<HEX(8,entry.shift_pc)<<endl;

    UINT8_T br_pred = cpu.predict_branch(entry.shift_pc);
    uint32_t branch_prediction = CAST(br_pred);

    //mispredict
    if(fetch_buffer[fetchIndex].taken != branch_prediction) {
      ++mispredicts;
      ++fetch_buffer[fetchIndex].mispredicted;
    } else { //correct predict
      //nothing to do
    }

    cpu.last_branch_result(fetch_buffer[fetchIndex].shift_pc,
                           (UINT8_T) fetch_buffer[fetchIndex].taken);


    exp_gh =  exp_gh << 1;
    exp_gh.set(0,fetch_buffer[fetchIndex].taken&0x1);

    exp_ph =  exp_ph << 1;
    exp_ph.set(0,fetch_buffer[fetchIndex].path&0x1);

    ++tst_idx;

    //cout<<"HERE mispredicts "<<mispredicts<<" of "<<lineNo<<endl;
    if(maxCount > 0 && lineNo>maxCount) {
      cout<<"-I: max count exceeded #"<<dec<<lineNo<<" "<<maxCount<<endl;
      break;
    }
  }             

  //every line in trace is a branch
  double numBr = (double) lineNo-1;
  double miss_pct = (double)100. * ((double)mispredicts / (double)numBr);

  cout<<"-I: end, miss %: "
      <<dec<<fixed<<setprecision(2)<<miss_pct
      <<dec<<setprecision(0)<<", "<<mispredicts<<" mispredicts"
      <<" in "<<dec<<numBr<<" branches"<<endl;

  return 0;
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
int main()
{
  cout<<"-I: begin"<<endl;
  
  string trace_input_fn       = "data/dhrystone_opt3.bare.hex";
  string history_trace_fn     = "history.txt";
  string loop_pred_entries_fn = "loop_pred_entries.txt";

  // ----------------------------------------------------------------
  string lp_transactions_fn = "lp_transactions.txt";
  string lp_tables_fn       = "lp_tables.txt";

  std::ofstream lpx(lp_transactions_fn.c_str());
  lp_os = &lpx;

  std::ofstream lpt(lp_tables_fn.c_str());
  // ----------------------------------------------------------------
  string tg_transactions_fn = "tg_transactions.txt";
  string tg_tables_fn       = "tg_tables.txt";

  std::ofstream tgx(tg_transactions_fn.c_str());
  tg_os = &tgx;

  std::ofstream tgt(tg_tables_fn.c_str());
  // ----------------------------------------------------------------
  
  O3_CPU cpu;

  bool limit   = false;
  bool filter  = true;
  int  cpu_num = 0;

  cpu.cpu = cpu_num;

  cpu.initialize_branch_predictor();

  int ret = begin(cpu,MAXCOUNT,trace_input_fn);

  if(!ret) {

    ofstream hist (history_trace_fn);
    ofstream lpred(loop_pred_entries_fn);

    hist<<"-I: MAXCOUNT "<<MAXCOUNT<<endl<<endl; 

    tage_predictor[cpu.cpu].dump_history(cpu.cpu,limit,filter,hist);
    loop_predictor[cpu.cpu].dump(filter,lpred);

    hist.close();
    lpred.close();

    //Final state of LP tables to lp_tables.txt for RTL compare
    lpx.close();

    lpt<<endl;
    loop_predictor[cpu.cpu].dump(false,lpt);
    lpt.close();

    //Final state of TAGE tables to tg_tables.txt for RTL compare
    tgx.close(); //transactions

    tgt<<endl;
    bool LIMIT = false;
    bool FILTER = true;
    tage_predictor[cpu.cpu].dump_comp_hist_length(tgt);
    tage_predictor[cpu_num].dump_pred_tables(cpu.cpu,LIMIT,FILTER,tgt);
    tage_predictor[cpu_num].dump_bimodal_table(LIMIT,FILTER,tgt);

    tgt.close();
  }

  cout<<"-I: See file history           : "<<history_trace_fn<<endl;
  cout<<"-I: See file loop pred xaction : "<<lp_transactions_fn<<endl;
  cout<<"-I: See file loop pred tables  : "<<lp_tables_fn<<endl;
  cout<<"-I: See file loop pred entries : "<<loop_pred_entries_fn<<endl;
  cout<<endl;
  cout<<"-I: See file tage pred xaction : "<<tg_transactions_fn<<endl;
  cout<<"-I: See file tage pred tables  : "<<tg_tables_fn<<endl;
  cout<<endl;

  return ret;
}
