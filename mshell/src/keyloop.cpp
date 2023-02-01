#include "mshell.h"
#include <sstream>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;
#define bforeach BOOST_FOREACH
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::mshLoop(void)
{
//  dmsg("+Mshell::run()");

//  _isExit = false;
  //Entering the loop with exit state returns false
  if(_isExit) {
    mshExit();
    return false;
  }

  history.clear();
  history.push_back("");
  cmd = "";
  _isExit = false;
  _mshBreakToPrompt = false;
  do {

    showPrompt();
    getline(cin,cmd);
//    if(cmd.length() == 0) continue;
    runMshCommand(cmd);

  } while(!_isExit && !_mshBreakToPrompt);

  //Exiting the loop due to exit state returns true
  if(_isExit) mshExit();
  _mshBreakToPrompt = false;
//  _isExit = false;
  return true;
}
// --------------------------------------------------------
// --------------------------------------------------------
void Mshell::mshExit()
{
  imsg("Exiting "+shellName+" shell");
  _isExit = true;
  mshIsExiting();
}
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_SERVER == 1
bool Mshell::runMshCommand(TcpServer &,string &cmd)
{
  return runMshCommand(cmd);
}
#endif
// --------------------------------------------------------
// Comments are stripped before calling runMshCommand();
// --------------------------------------------------------
bool Mshell::runMshCommand(string &cmd)
{
//  dmsg("+Mshell::runMshCommand()");

#if MSHELL_CLIENT == 1
  if(_mshEcho) { msg->msg("\n\n  <msclient echo>: "+cmd); }
#else
  if(_mshEcho) { msg->msg("\n\n  <mshell echo>: "+cmd); }
#endif

  vector<string> cmdVec;
  tokenize(cmd,cmdVec);

  if(!_isScript && cmd.length() > 0) history.push_back(cmd);
  if(cmdVec.size() > 0 && !_isScript) cout<<endl;

  if(detectAndRunCmd(cmdVec)) {
    if(!_isScript) showPrompt();
    if(_isExit) return true;
  } else {
    emsg(errCode);
    showPrompt();
    return false;
  }
  return true;
}
// --------------------------------------------------------
// --------------------------------------------------------
void Mshell::bufferReplace(uint32_t pos,string s)
{
  lineBuffer.replace(pos,s.length(),s);
  bufferPos = lineBuffer.size();
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mshell::isFileAccess(void)
{
  int idx=0;
  int pos=-1;
  vector<string> fileCommands;
  fileCommands.push_back("src ");
  fileCommands.push_back("source ");
  fileCommands.push_back("sh ");
  fileCommands.push_back("shell ");
  bforeach(string cmd, fileCommands) {
    idx = lineBuffer.find(cmd);
    if(idx != -1) {
      pos = idx+cmd.length();
      break;
    }
  }

  if(pos == -1) return false;

  stringstream ss; ss << pos;
  string subs = lineBuffer.substr(pos);

  string pipeOutput;
  FILE *pipe = popen("ls", "r");
  if (!pipe) { return false; }

  char buffer[4096];

  while(fgets(buffer,4096,pipe) != NULL) {
    pipeOutput.append(buffer);
  }

  pclose(pipe);
  vector<string> lsTokens,matches;
  split(lsTokens, pipeOutput, is_any_of("\n"));

  bforeach(string tok,lsTokens) {
    if(starts_with(tok,subs)) { matches.push_back(tok); }
  }

  if(matches.size() == 1) 
    bufferReplace(pos-1,string(" ")+matches[0]);
  else bforeach(string t,matches) {
    msg->msg(t);
  }

  return true;
}
#undef bforeach
