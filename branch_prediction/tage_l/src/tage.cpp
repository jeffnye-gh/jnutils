#include "ooo_cpu.h"
#include "tage.h"

#include <iostream>
#include <iomanip>
#include <ostream>
#include <string>
#include <cmath>
using namespace std;

extern int tst_idx;
extern std::ostream *tg_os;

int tage_predictor_table_entry::dump_final_tpt_entry(
        int tst_idx,
        int index,
        int component,
        bool filter,
        std::ostream &os)
{
  uint32_t _tag = tag;
  uint32_t _ctr = CAST(ctr);
  uint32_t _use = CAST(useful);

  int not_default = 0;
  if(_tag != 0 || _ctr != 4 || _use != 0) not_default = 1;

  if(!filter || not_default == 1) {
    os<<"-I: cmp:"<<dec<<component
      <<" a:0x"<<HEX(4,index)
      <<" t:0x"<<HEX(4,_tag)
      <<" c2:0x"<<HEX(2,_use)
      <<" c1:0x"<<HEX(2,_ctr)
//      <<" v:1"
      <<endl;
  }
  return not_default;
}

int tage_predictor_table_entry::dump_tpt_entry(
        int tst_idx,
        int index,
        int component,
        bool filter,
        int64_t ip,
        std::ostream &os
)
{
  uint32_t _tag = tag;
  uint32_t _ctr = CAST(ctr);
  uint32_t _use = CAST(useful);

  int not_default = 0;

  uint32_t _reg_wr_data = 0x3F & ((CAST(useful) << 4 ) | (CAST(ctr) << 1));

  if(_tag != 0 || _ctr != 4 || _use != 0) not_default = 1;

  if(!filter || not_default == 1) {

    os<<"-I: 150 tg tpt entry alloc"
      <<" tst_idx:" <<dec<<tst_idx
      <<" pc:0x"    <<HEX(8,ip)
      <<" cmp:"     <<dec<<component
      <<" a:0x"     <<HEX(4,index)<<"("<<dec<<index<<")"
      <<" t:0x"     <<HEX(4,_tag)
      <<" c2:0x"    <<HEX(1,_use)
      <<" c1:0x"    <<HEX(1,_ctr)
      <<endl;
  }

  return not_default;
}



//int tage_predictor_table_entry::dump(
//        int index,int comp,bool filter,std::ostream &os)
//{
//  uint32_t _tag = tag;
//  uint32_t _ctr = CAST(ctr);
//  uint32_t _use = CAST(useful);
//  int not_default = 0;
//  if(_tag != 0 || _ctr != 4 || _use != 0) not_default = 1;
//  if(!filter || not_default == 1) {
//    os<<"-I: cmp:"<<DEC<<comp
//      <<" a:"<<HEX(2,index)
//      <<" t:"<<HEX(4,_tag)
//      <<" c2:"<<HEX(1,_use)
//      <<" c1:"<<HEX(1,_ctr)
//      <<" v:1" //if it is in the table it is valid
//      <<endl;
//  }
//  return not_default;
//}

// --------------------------------------------------------------------
void Tage::dump_pred_tables(int cpu,bool limit,bool filter,std::ostream &os)
{
//  os<<"-I: Tage cpu "<<dec<<cpu<<endl;
//  os<<"-I: predictor_tables ("<<TAGE_NUM_COMPONENTS<<")"<<endl;
  uint32_t not_default = 0;
  for(size_t y=0;y<TAGE_NUM_COMPONENTS;++y) {

    os<<endl<<"-I: tg table cmp:"<<dec<<y<<endl;
    size_t how_many = limit ? 10 : pow(2,CAST(TAGE_INDEX_BITS[y]));

    for(size_t x=0;x<how_many;++x) {
      not_default
        += predictor_table[y][x].dump_final_tpt_entry(tst_idx,x,y,filter,os);
    }

    os<<"-I:   table #entries not default: "<<not_default<<endl;
    not_default = 0;
  }
}

// --------------------------------------------------------------------
void Tage::dump_bimodal_table(bool limit,bool filter,std::ostream &os)
{
  os<<endl<<"-I: bimodal table"<<endl;
  size_t how_many = limit ? 8 : TAGE_BIMODAL_TABLE_SIZE;
  uint32_t not2 = 0;
  for(size_t i=0;i<how_many;++i) {
    uint32_t value = CAST(bimodal_table[i]);
    if(value != 2) ++not2;
    if((filter && value != 2 ) || !filter) {
      os<<"-I: idx:0x"<<HEX(4,i)
        <<" ctr:0x"<<HEX(1,value)
        <<" val:1" //if it is in the table it is valid
        <<endl;
    }
  }
  os<<"-I: bimodal #entries not default: "<<not2<<endl;
}
// --------------------------------------------------------------------
void Tage::dump(int cpu,bool limit,bool filter,std::ostream &os)
{
  os<<"-I: Tage cpu "<<dec<<cpu<<endl;
  os<<"-I:   num_branches  "<<num_branches<<endl;
  os<<"-I:   use_alt_on_na u8 "<<CAST(use_alt_on_na)<<endl;
  os<<"-I:   tage_pred     u8 "<<CAST(tage_pred)<<endl;
  os<<"-I:   pred          u8 "<<CAST(pred)<<endl;
  os<<"-I:   alt_pred      u8 "<<CAST(alt_pred)<<endl;
  os<<"-I:   pred_comp        "<<CAST(pred_comp)<<endl;
  os<<"-I:   alt_comp         "<<CAST(alt_comp)<<endl;
  os<<"-I:   STRONG           "<<CAST(STRONG)<<endl;
  os<<"-I: bimodal_table limit("<<limit<<") filter("<<filter<<")"<<endl;

  dump_comp_hist_length(os);
  dump_bimodal_table(limit,filter,os);
  dump_pred_tables(cpu,limit,filter,os);
  dump_history(cpu,limit,filter,os);
}
// --------------------------------------------------------------------
// --------------------------------------------------------------------
void Tage::dump_comp_hist_length(std::ostream &os)
{
  for(int i = 0;i<TAGE_NUM_COMPONENTS;++i) {
    int h = component_history_lengths[i];
    //i + 1  table names are conventionally indexed from 1, T1...
    os<<"-I: tg cmp "<<DEC<<(i+1)<<" hist len "<<DEC<<CAST(h)<<endl;
  }
}
// --------------------------------------------------------------------
// --------------------------------------------------------------------
void Tage::dump_history(int cpu,bool limit,bool filter,std::ostream &os)
{
  os<<"-I: Tage cpu "<<dec<<cpu<<" limit "<<limit<<" filter "<<filter<<endl;
  os<<"-I:   global_history ("<<TAGE_GLOBAL_HISTORY_BUFFER_LENGTH<<")"<<endl;
  size_t how_many = limit ? 10 : TAGE_GLOBAL_HISTORY_BUFFER_LENGTH;
  string gs;
  for(size_t i=0;i<how_many;++i) {
    uint32_t d = CAST(global_history[i]);
    gs = ::to_string(d) + gs;
    //os<<"-I "<<dec<<i<<" "<<CAST(global_history[i])<<endl; 
  }
  os<<"-I full ghr: "<<gs<<endl;

  os<<"-I:   path_history   ("<<TAGE_PATH_HISTORY_BUFFER_LENGTH<<")"<<endl;
  how_many = limit ? 10 : TAGE_PATH_HISTORY_BUFFER_LENGTH;
  string ps = "";
  for(size_t i=0;i<how_many;++i) {
    uint32_t d = CAST(path_history[i]);
    ps = ::to_string(d) + ps;
    //os<<"-I "<<i<<" "<<CAST(path_history[i])<<endl; 
  }
// Not useful now
//  os<<"-I full phr: "<<ps<<endl;

  std::string last_chars = "";

  if(gs.length() >= TAGE_FOLDED_HISTORY_BUFFER_LENGTH) {
    last_chars = gs.substr(gs.length() - TAGE_FOLDED_HISTORY_BUFFER_LENGTH);
  }
  else {
    last_chars = gs;
  }

  os<<"-I fhr:  "<<TAGE_FOLDED_HISTORY_BUFFER_LENGTH<<": "<<last_chars<<endl;

  if(ps.length() >= TAGE_PATH_HISTORY_BUFFER_LENGTH) {
    last_chars = ps.substr(ps.length() - TAGE_PATH_HISTORY_BUFFER_LENGTH);
  } else {
    last_chars = ps;
  }

  os<<"-I phr:  "<<TAGE_PATH_HISTORY_BUFFER_LENGTH<<": "<<last_chars<<endl;

}

//Tage tage_predictor[NUM_CPUS];


//void O3_CPU::initialize_branch_predictor()
//{
//    tage_predictor[cpu].init();
//}
//
//uint8_t O3_CPU::predict_branch(uint64_t ip)
//{
//    return tage_predictor[cpu].predict(ip);
//}
//
//void O3_CPU::last_branch_result(uint64_t ip, uint8_t taken)
//{
//    tage_predictor[cpu].update(ip, taken);
//}

void Tage::init()
{
    /*
    Initializes the member variables
    */
    use_alt_on_na = 8;
    tage_pred = 0;
    for (int i = 0; i < TAGE_BIMODAL_TABLE_SIZE; i++)
    {
        bimodal_table[i] = (1 << (TAGE_BASE_COUNTER_BITS - 1)); // weakly taken
    }
    for (int i = 0; i < TAGE_NUM_COMPONENTS; i++)
    {
        for (int j = 0; j < (1 << TAGE_INDEX_BITS[i]); j++)
        {
            predictor_table[i][j].ctr = (1 << (TAGE_COUNTER_BITS - 1)); // weakly taken
            predictor_table[i][j].useful = 0;                           // not useful
            predictor_table[i][j].tag = 0;
        }
    }

    double power = 1;
    for (int i = 0; i < TAGE_NUM_COMPONENTS; i++)
    {
        component_history_lengths[i] = int(TAGE_MIN_HISTORY_LENGTH * power + 0.5); // set component history lengths
        power *= TAGE_HISTORY_ALPHA;
    }

    component_history_lengths[TAGE_NUM_COMPONENTS-1] = 640;
    num_branches = 0;
}

uint8_t Tage::get_prediction(uint64_t ip, int comp)
{
    /*
    Get the prediction according to a specific component 
    */
    if(comp == 0) // Check if component is the bimodal table
    {
        Index index = get_bimodal_index(ip); // Get bimodal index
        return bimodal_table[index] >= (1 << (TAGE_BASE_COUNTER_BITS - 1));
    }
    else
    {
        Index index = get_predictor_index(ip, comp); // Get component-specific index
        return predictor_table[comp - 1][index].ctr >= (1 << (TAGE_COUNTER_BITS - 1));
    }
}

uint8_t Tage::predict(uint64_t ip)
{
    pred_comp = get_match_below_n(ip, TAGE_NUM_COMPONENTS + 1); // Get the first predictor from the end which matches the PC
    alt_comp = get_match_below_n(ip, pred_comp); // Get the first predictor below the provider which matches the PC 

//cout<<"HERE "<<HEX(8,ip)<<dec<<" "<<CAST(pred_comp)<<" "<<CAST(alt_comp)<<endl;

    //Store predictions for both components for use in the update step
    pred = get_prediction(ip, pred_comp);
    alt_pred = get_prediction(ip, alt_comp);


    if(pred_comp == 0)
        tage_pred = pred;
    else
    {
        Index index = get_predictor_index(ip, pred_comp);
        STRONG = abs(2 * predictor_table[pred_comp - 1][index].ctr + 1 - (1 << TAGE_COUNTER_BITS)) > 1;
        if (use_alt_on_na < 8 || STRONG) // Use provider component only if USE_ALT_ON_NA < 8 or the provider counter is strong
            tage_pred = pred;
        else
            tage_pred = alt_pred;
    }
    return tage_pred;
}

void Tage::ctr_update(uint8_t &ctr, int cond, int low, int high)
{
    /*
    Function to update bounded counters according to some condition
    */
    if(cond && ctr < high)
        ctr++;
    else if(!cond && ctr > low)
        ctr--;
}

Index Tage::get_bimodal_index(uint64_t ip)
{
    /*
    Return index of the PC in the bimodal table using the last K bits
    */
    return ip & (TAGE_BIMODAL_TABLE_SIZE - 1);
}

Path Tage::get_path_history_hash(int component)
{
    /*
    Use a hash-function to compress the path history
    */
    Path A = 0;

    int size = component_history_lengths[component - 1] > 16 ? 16 : component_history_lengths[component-1]; // Size of hash output
    for (int i = TAGE_PATH_HISTORY_BUFFER_LENGTH - 1; i >= 0; i--)
    {
        A = (A << 1) | path_history[i]; // Build the bit vector a using the path history array
    }

    A = A & ((1 << size) - 1);
    Path A1;
    Path A2;
    A1 = A & ((1 << TAGE_INDEX_BITS[component - 1]) - 1); // Get last M bits of A
    A2 = A >> TAGE_INDEX_BITS[component - 1]; // Get second last M bits of A

    // Use the hashing from the CBP-4 L-Tage submission
    A2 = ((A2 << component) & ((1 << TAGE_INDEX_BITS[component - 1]) - 1)) + (A2 >> abs(TAGE_INDEX_BITS[component - 1] - component));
    A = A1 ^ A2;
    A = ((A << component) & ((1 << TAGE_INDEX_BITS[component - 1]) - 1)) + (A >> abs(TAGE_INDEX_BITS[component - 1] - component));

    return (A);
}

History Tage::get_compressed_global_history(int inSize, int outSize)
{
    /*
    Compress global history of last 'inSize' branches into 'outSize' by wrapping the history
    */
    History compressed_history = 0; // Stores final compressed history
    History temporary_history = 0; // Temorarily stores some bits of history
    int compressed_history_length = outSize;
    for (int i = 0; i < inSize; i++)
    {
        if (i % compressed_history_length == 0)
        {
            compressed_history ^= temporary_history; // XOR current segment into the compressed history
            temporary_history = 0;
        }
        temporary_history = (temporary_history << 1) | global_history[i]; // Build history bit vector
    }
    compressed_history ^= temporary_history;
    return compressed_history;
}

Index Tage::get_predictor_index(uint64_t ip, int component)
{
    /*
    Get index of PC in a particular predictor component
    */
    Path path_history_hash = get_path_history_hash(component); // Hash of path history

    // Hash of global history
    History global_history_hash = get_compressed_global_history(component_history_lengths[component - 1], TAGE_INDEX_BITS[component - 1]);

    return (global_history_hash ^ ip ^ (ip >> (abs(TAGE_INDEX_BITS[component - 1] - component) + 1)) ^ path_history_hash) & ((1 << TAGE_INDEX_BITS[component-1]) - 1);
}

Tag Tage::get_tag(uint64_t ip, int component)
{
    /*
    Get tag of a PC for a particular predictor component
    */
    History global_history_hash = get_compressed_global_history(component_history_lengths[component - 1], TAGE_TAG_BITS[component - 1]);
    global_history_hash ^= get_compressed_global_history(component_history_lengths[component - 1], TAGE_TAG_BITS[component - 1] - 1);

    return (global_history_hash ^ ip) & ((1 << TAGE_TAG_BITS[component - 1]) - 1);
}



int Tage::get_match_below_n(uint64_t ip, int component)
{
    /*
    Get component number of first predictor which has an entry for the IP below a specfic component number
    */
    for (int i = component - 1; i >= 1; i--)
    {
        Index index = get_predictor_index(ip, i);
        Tag tag = get_tag(ip, i);

        if (predictor_table[i - 1][index].tag == tag) // Compare tags at a specific index
        {
            return i;
        }
    }

    return 0; // Default to bimodal in case no match found
}

Tage::Tage()
{
}

Tage::~Tage()
{
}


//
// function to update the state (member variables) of the tage class
//
void Tage::update(uint64_t ip, uint8_t taken)
{
    // the predictor component is not the bimodal table
    if (pred_comp > 0)
    {
        struct tage_predictor_table_entry *entry
             = &predictor_table[pred_comp - 1]
                               [get_predictor_index(ip, pred_comp)];

        uint8_t useful = entry->useful;

        if(!STRONG)
        {
            if (pred != alt_pred) {
                ctr_update(use_alt_on_na, !(pred == taken), 0, 15);
            }
        }

        // alternate component is not the bimodal table
        if(alt_comp > 0)
        {
            struct tage_predictor_table_entry *alt_entry
                 = &predictor_table[alt_comp - 1]
                                   [get_predictor_index(ip, alt_comp)];
            // update ctr for alternate predictor if useful for predictor is 0
            if(useful == 0) {
                ctr_update(alt_entry->ctr, taken, 0,
                          ((1 << TAGE_COUNTER_BITS) - 1));
            }
        }
        else
        {
            Index index = get_bimodal_index(ip);
            // update ctr for alternate predictor if useful for predictor is 0
            if (useful == 0) {
                ctr_update(bimodal_table[index], taken, 0,
                          ((1 << TAGE_BASE_COUNTER_BITS) - 1));
            }
        }

        // update u
        if (pred != alt_pred)
        {
            if (pred == taken)
            {
                if (entry->useful < ((1 << TAGE_USEFUL_BITS) - 1))
                    entry->useful++;  // if prediction from preditor component was correct
            }
            else
            {
                if(use_alt_on_na < 8)
                {
                    if (entry->useful > 0)
                        entry->useful--;  // if prediction from altpred component was correct
                } 
            }
        }

        ctr_update(entry->ctr, taken, 0, ((1 << TAGE_COUNTER_BITS) - 1));  // update ctr for predictor component
    }
    else
    {
        Index index = get_bimodal_index(ip);
        ctr_update(bimodal_table[index], taken, 0, ((1 << TAGE_BASE_COUNTER_BITS) - 1));  // update ctr for predictor if predictor is bimodal
    }

    // allocate tagged entries on misprediction
    if (tage_pred != taken)
    {
//HACK - remove the rand()
//        long rand = random();
//        rand = rand & ((1 << (TAGE_NUM_COMPONENTS - pred_comp - 1)) - 1);  
        int start_component = pred_comp + 1;

//        //compute the start-component for search
//        if (rand & 1)  // 0.5 probability
//        {
//            start_component++;
//            if (rand & 2)  // 0.25 probability
//                start_component++;
//        }

        //Allocate atleast one entry if no free entry
        int isFree = 0;
        for (int i = pred_comp + 1; i <= TAGE_NUM_COMPONENTS; i++)
        {
            struct tage_predictor_table_entry *entry_new = &predictor_table[i - 1][get_predictor_index(ip, i)];
            if (entry_new->useful == 0)
                isFree = 1;
        }
        if (!isFree && start_component <= TAGE_NUM_COMPONENTS)
            predictor_table[start_component - 1][get_predictor_index(ip, start_component)].useful = 0;
        
        
        // search for entry to steal from the start-component till end
        for (int i = start_component; i <= TAGE_NUM_COMPONENTS; i++)
        {
            struct tage_predictor_table_entry *entry_new = &predictor_table[i - 1][get_predictor_index(ip, i)];
            if (entry_new->useful == 0)
            {
                entry_new->tag = get_tag(ip, i);
                entry_new->ctr = (1 << (TAGE_COUNTER_BITS - 1));
                break;
            }
        }
    }

    // update global history
    for (int i = TAGE_GLOBAL_HISTORY_BUFFER_LENGTH - 1; i > 0; i--)
        global_history[i] = global_history[i - 1];
    global_history[0] = taken;

    // update path history
    for (int i = TAGE_PATH_HISTORY_BUFFER_LENGTH - 1; i > 0; i--)
        path_history[i] = path_history[i - 1];

    path_history[0] = ip & 1;
    
    // graceful resetting of useful counter
    num_branches++;
    if (num_branches % TAGE_RESET_USEFUL_INTERVAL == 0)
    {
        num_branches = 0;
        for (int i = 0; i < TAGE_NUM_COMPONENTS; i++)
        {
            for (int j = 0; j < (1 << TAGE_INDEX_BITS[i]); j++)
                predictor_table[i][j].useful >>= 1;
        }
    }
}
