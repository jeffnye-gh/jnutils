#include "jndbg.h"
#include <boost/algorithm/string.hpp>

using namespace std;

struct XregComparator {
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        // Extract the numeric part of the keys
        int lhs_num = std::stoi(lhs.substr(1));
        int rhs_num = std::stoi(rhs.substr(1));
        // Compare based on the numeric values
        return lhs_num < rhs_num;
    }
};
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
void Jndbg::writeXregs()
{
  std::map<std::string, XregFieldInfo, XregComparator> sorted(xregs.begin(), xregs.end());

  xregsGolden << "count: "<<xreg_update_count<<endl;
  for(auto &[key,val] : sorted) {
    xregsGolden << key<<":"<<val.data << endl;
  }

  ++xreg_update_count;
}
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
bool Jndbg::readXregsChangeFile(ifstream &in,map<string,string> &contents)
{
  std::string line;
  while (std::getline(in, line)) {
    vector<string> splitVec;
    boost::split(splitVec, line,boost::is_any_of(":"));
    if(splitVec.size() != 2) {
      wr_status("malformed xregs data");
      std::this_thread::sleep_for(std::chrono::seconds(1));
      return false; 
    }
    contents.insert(make_pair(splitVec[0],splitVec[1]));
  }
  return true;
}
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
void Jndbg::onXregsFileChanged()
{
  wr_status("xregs updated");
  ifstream in(XREGS_WATCH_FILE);
  if(!in.is_open()) {
    wr_status("Failed to open "+XREGS_WATCH_FILE);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return;
  }

  map<string,string> contents;
  if(!readXregsChangeFile(in,contents)) return;

  in.close();

  clearXregActives();

  for(auto &[key,val] : contents) {
    map<string,XregFieldInfo>::iterator q = xregs.find(key);
    if(q != xregs.end()) {
      if(q->second.data != val) {
        q->second.data = val;
        q->second.active = "*";
      }
    }
  }

  drawXregsContent();

  writeXregs();
  wr_status("Ready");
}
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
void Jndbg::onCsrsFileChanged()
{
  wr_status("csrs updated");
}
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
void Jndbg::onExecutionFileChanged()
{
  wr_status("execution state updated");
}

