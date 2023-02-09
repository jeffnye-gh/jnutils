// --------------------------------------------------------------------
// Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
#include "mshell.h"
#include "mstest.h"
#include "msg.h"

#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <fstream>
#include <sstream>

using namespace std;
using namespace boost;

#define bforeach BOOST_FOREACH
#define bb boost::bind

#define PB(s) ms.helpVec.push_back(s)
#define RB(s) ms.relNotesVec.push_back(s)
#define VB(s) ms.versionVec.push_back(s)
// ======================================================================
// ======================================================================
Mstest::Mstest(Mshell &_ms)
  : ms(_ms)
{
  msg->verbose=100;
  PB("===================================================================");
  PB("MSTEST specific commands");
  PB("===================================================================");
  PB("  placeholder");
  PB("");

  RB("MSTEST RELEASE NOTES");
  RB("  -changes for version placeholder");
  RB("    * placeholder change");
  RB("");

  VB("MSTEST");
  VB("Version: x.y.z");
  VB("Contact: Jeff");
  VB("");
}
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
bool Mstest::undef(vector<string>  &s)
  { msg->emsg("Undefined function called from mshell."); return false; }
// --------------------------------------------------------
// --------------------------------------------------------
bool Mstest::srcFile(vector<string>  &s)
{
  if(s.size() <= 1) {
     msg->emsg("'src' : no file specified");
     return false;
  }

  fstream in(s[1].c_str(),ios::in);
  if(!in.is_open()) {
    msg->emsg("Could not open file '"+s[1]+string("'"));
    return false;
  } else {
    msg->imsg("sourcing file '"+s[1]+string("'"));
  }
  char buf[2048];
  string str;
  bool err = false;
  int lineNum=1;
  ms.isScript(true);
  while(in.getline(&buf[0],2048)) {
    str = buf;
    msg->dmsg("#"+::to_string(lineNum)+" msh> '"+str+"'");
    if(!ms.runMshCommand(str)) {
      err = true;
      break;
    }
    ++lineNum;
  }
  ms.isScript(false);
  in.close();
  if(err) {
    stringstream lnstr; lnstr << lineNum;
    msg->emsg("Error on line "+lnstr.str()+" of file "+s[1]);
    return false;
  }
  return true;
}
// --------------------------------------------------------
// atm this is the same for all commands
// --------------------------------------------------------
inline bool Mstest::appCmd(uint32_t i,vector<string>  &t)
{
  return ms.cmdMap[i](t);
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mstest::dispatch(vector<string>  &t)
{
  if(t[0] == "src" || t[0] == "source")
    { return appCmd(M_SRC_FILE,t); }

  if(t[0] == "setvar")
    { return appCmd(M_SET_VAR,t); }

  if(t[0] == "showvar")
    { return appCmd(M_SET_VAR,t); }

  if(t[0] == "showvars")
    { return appCmd(M_SHOW_VARS,t); }

  if(t[0] == "showsettings")
    { return appCmd(M_SHOW_SETTINGS,t); }

  if(t[0] == "r" || t[0] == "run")
    { return appCmd(M_RUN,t); }

  if(t[0] == "reset")
    { return appCmd(M_RESET,t); }

  if(t[0] == "forcefail")
    { return appCmd(M_FORCE_FAIL,t); }

  msg->emsg("Unknown app command "+t[0]);
  ms.errCode = Mshell::SYNTAX_ERROR;
  ms.errText = "token was "+t[0];
  return false;
}
// --------------------------------------------------------
// --------------------------------------------------------
bool Mstest::setVar(vector<string> &)
  { msg->imsg("called setVar"); return true; }
// --------------------------------------------------------
bool Mstest::showVar(vector<string> &)
  { msg->imsg("called showVar"); return true; }
// --------------------------------------------------------
bool Mstest::showVars(vector<string> &)
  { msg->imsg("called showVars"); return true; }
// --------------------------------------------------------
bool Mstest::showSettings(vector<string> &)
  { msg->imsg("called showSettings"); return true; }
// --------------------------------------------------------
bool Mstest::run(vector<string> &)
  { msg->imsg("called run"); return true; }
// --------------------------------------------------------
bool Mstest::reset(vector<string> &)
  { msg->imsg("called reset"); return true; }
// --------------------------------------------------------
bool Mstest::forceFail(vector<string> &)
  { msg->imsg("called forceFail"); return false; }
// --------------------------------------------------------
bool Mstest::respondToClient(vector<string> &)
  { msg->imsg("called respondToClient()"); return true; }
// --------------------------------------------------------
void buildCmdMap(map<uint32_t,Mshell::Cmd> &fm, Mstest &mst)
{
  fm.insert(
    make_pair(Mstest::M_CMD_HANDLER,bb(&Mstest::dispatch,mst,_1)));

  fm.insert(
    make_pair(Mstest::M_SRC_FILE,bb(&Mstest::srcFile,mst,_1)));

  fm.insert(
    make_pair(Mstest::M_SET_VAR,bb(&Mstest::setVar,mst,_1)));

  fm.insert(
    make_pair(Mstest::M_SHOW_VAR,bb(&Mstest::showVar,mst,_1)));

  fm.insert(
    make_pair(Mstest::M_SHOW_VARS,bb(&Mstest::showVars,mst,_1)));

  fm.insert(
    make_pair(Mstest::M_SHOW_SETTINGS,bb(&Mstest::showSettings,mst,_1)));

  fm.insert(
    make_pair(Mstest::M_RUN,bb(&Mstest::run,mst,_1)));

  fm.insert(
    make_pair(Mstest::M_RESET,bb(&Mstest::reset,mst,_1)));

  fm.insert(
    make_pair(Mstest::M_RESPOND_CLIENT,bb(&Mstest::respondToClient,mst,_1)));

  fm.insert(
    make_pair(Mstest::M_FORCE_FAIL,bb(&Mstest::forceFail,mst,_1)));
}

#undef bb
#undef bforeach
#undef PB
#undef RB
#undef VB
