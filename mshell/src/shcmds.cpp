#include "mshell.h"

using namespace std;
const string Mshell::MSHELL_VERSION = "0.1.0";
// --------------------------------------------------------
// --------------------------------------------------------
vector<string> Mshell::versionVec = {
"Mshell",
"Version: "+string(MSHELL_VERSION),
"Contact: Jeff Nye",
""
};
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::mshShowVersion(void)
{
  for(size_t i=0;i<versionVec.size();++i) out<<versionVec[i]<<endl;
  return true;
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::mshEcho(string s)
{
  msg->msg(s+"\n"); 
  return true;
}
void Mshell::mshIsExiting() { /* for future clean up actions */ }
