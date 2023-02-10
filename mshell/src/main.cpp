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
// ---------------------------------------------------------------------------
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
  Mshell mshell(std::cout);
  msg->setWho("mshell");

  mshell.setShellName("mstest");
  mshell.setPrompt("mstest> ");
  mshell.setMshShowRet(true);

  Mstest mstest(mshell);

  map<uint32_t,Mshell::Cmd> voidList;
  buildCmdMap(voidList,mstest);
  mshell.setCmdMap(voidList);

  bool ok = mshell.mshLoop();
  if(!ok) return 1;
  return 0;
}
