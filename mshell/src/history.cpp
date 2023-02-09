// --------------------------------------------------------------------
// Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
#include "mshell.h"
#include <sstream>
using namespace std;
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::addHistory(string cmd)
{
  if(cmd.length() > 0) history.push_back(cmd);
  historyIndex = history.size() - 1;
  return true;
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::addHistory(void)
{
  if(lineBuffer.length() > 0) history.push_back(lineBuffer);
  historyIndex = history.size() - 1;
  return true;
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::revHistory(void)
{
  lineBuffer = history[historyIndex];
  if(historyIndex > 1) --historyIndex;
  return true;
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::fwdHistory(void)
{
  lineBuffer = history[historyIndex];
  if(historyIndex < history.size()-1) ++historyIndex;
  return true;
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::shellShowHistory(void)
{
  for(uint32_t i=1;i<history.size();++i) {
    stringstream s;
    s << i;
    _msg("["+s.str()+"] "+history[i]);
  }
  _msg("");
  return true;
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::runBangEvent(vector<string> &t)
{
  vector<string> histTokens;
  uint32_t i=0;
  stringstream ss;

  string bangNum = t[0].substr(1);
  if(bangNum == "!") {
    i = history.size()-1;
  } else {
    ss<<bangNum; ss >> i;
  }

  if(i!=0) {
    if(i>history.size()-1) {
      errCode = EVENT_NOT_FOUND;
      return false;
    }
    history[history.size()-1] = history[i];
    tokenize(history[i],histTokens);
    return(detectAndRunCmd(histTokens));
  }
  return true;
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::isBangEvent(string &c)
  { uint32_t idx = c.find("!"); if(idx == 0) return true; return false; }
