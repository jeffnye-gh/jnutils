#include "mshell.h"
#include "mstest.h"
#include "msg.h"

#include <map>
using namespace std;

Msg *Msg::instance = 0;
std::unique_ptr <Msg> msg(Msg::getInstance());
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
extern void buildCmdMap(map<uint32_t,Mshell::Cmd>&,Mstest&);
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
int main(int ac, char **av)
{
//  Msg msg;
//  msg.setWho("mstest");
//  msg.verbose = 10;

  Mshell mshell(std::cout);

  mshell.setShellName("mstest");
  mshell.setPrompt("mstest> ");
  mshell.setMshShowRet(true);
//  mshell.setMsg(&msg);

  Mstest mstest(mshell);

  map<uint32_t,Mshell::Cmd> voidList;
  buildCmdMap(voidList,mstest);
  mshell.setCmdMap(voidList);

  bool ok = mshell.mshLoop();
  if(!ok) return 1;
  return 0;
}
