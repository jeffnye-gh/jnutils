// ----------------------------------------------------------------------------
// This file is part of jnutils, made public 2023, (c) Jeff Nye
//
// jnutils is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// jnutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with jnutils; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
// ----------------------------------------------------------------------------
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
