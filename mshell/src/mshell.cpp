// --------------------------------------------------------------------------
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
// ---------------------------------------------------------------------------
#include "msg.h"
#include "mshell.h"

#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <ostream>

using namespace std;
using namespace boost;

#define bforeach BOOST_FOREACH
Mshell *MSH;
// =======================================================================
Mshell::Mshell(std::ostream &o)
  : out(o),
    history(),
    cmdArgs(),
    cmdMap()
{
  MSH = this;
}
// -----------------------------------------------------------------------
bool Mshell::detectAndRunCmd(vector<string> &txtTokens)
{
  if(txtTokens.size() == 0) return true;

  if(txtTokens[0] == "q" || txtTokens[0] == "quit" || txtTokens[0] == "exit")
    { return reportRet(mshCommand(S_EXIT,txtTokens)); }

  if(isBangEvent(txtTokens[0]))
    { return reportRet(mshCommand(S_BANG_EVENT,txtTokens)); }

  if(txtTokens[0] == "h" || txtTokens[0] == "history")
    { return reportRet(mshCommand(S_HISTORY,txtTokens)); }

  if(txtTokens[0] == "??" || txtTokens[0] == "?" || txtTokens[0] == "help")
    { return reportRet(mshCommand(S_SHORT_HELP,txtTokens)); }

  if(txtTokens[0] == "version")
    { return reportRet(mshCommand(S_VERSION,txtTokens)); }

  if(txtTokens[0] == "sh" || txtTokens[0] == "os")
    { return reportRet(mshCommand(S_OS_CMD,txtTokens)); }

  if(txtTokens[0] == "tcp")
    { return reportRet(mshCommand(S_TCP,txtTokens)); }

  //UP_ARROW ?
  //DWN_ARROW ?

  if(txtTokens[0] == "echo")
    { return mshCommand(S_ECHO,txtTokens); }

  if(txtTokens[0] == "rnotes" || txtTokens[0] == "releasenotes")
    { return mshCommand(S_RELEASE_NOTES,txtTokens); }

  //handle comments at the beginning of a string
  int idx = txtTokens[0].find("//");
  if(idx != -1) return true;

  //this is not a shell command, must be a app command
  return reportRet(appCommand(USER_TYPE,txtTokens));
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::reportRet(bool b)
{
  if(_mshShowRet) {
    _msg("[ "+::to_string(b)+" ]");
  }
  return b;
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::mshCommand(uint32_t i,vector<string> &t)
{
  string command;
  switch(i)
  {
    case S_OS_CMD:
    case S_ECHO:
      for(unsigned int i=1;i<t.size();++i)
        { command += string(" ") + t[i]; }
      break;
    default: command = "";
  }

  switch(i) {
    //explicit exit command returns true
    case S_EXIT:          { mshExit(); return true; }
    case S_HELP:          return shellShowHelp(true);
    case S_HISTORY:       return shellShowHistory();
    case S_RELEASE_NOTES: return shellShowReleaseNotes();
    case S_SHORT_HELP:    return shellShowHelp(false);
    case S_TCP:           return shellTcp(t);
    case S_VERSION:       return mshShowVersion();

    case S_BANG_EVENT:    return runBangEvent(t);

    case S_OS_CMD:        system(command.c_str()); return true;

    case S_ECHO:          return mshEcho(command);
    case S_UP_ARROW:
    case S_DWN_ARROW:
    default: emsg("Unknown shell command"); break;
  }
  return true;
//  return false;
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::appCommand(uint32_t i,vector<string> &t)
  { return cmdMap[i](t); }
// --------------------------------------------------------
// --------------------------------------------------------
void Mshell::tokenize(string &c,vector<string> &keys)
{
  keys.clear();
  if(c.length() == 0) return;

  char_separator<char> sep(" ");
  MsTokenizer txtTokens(c,sep);

  MsTokenizer::iterator ti,tiend;
  for(ti = txtTokens.begin(); ti != tiend; ++ti)
  {
    keys.push_back(*ti);
  }
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::isExit(void)     { return _isExit; }
bool Mshell::isScript(void)   { return _isScript; }
void Mshell::isScript(bool b) { _isScript = b; }
// --------------------------------------------------------
// --------------------------------------------------------
void Mshell::showPrompt(bool force)
{
//  if(!_isScript || force) out<<prompt;
  out<<prompt;
}
