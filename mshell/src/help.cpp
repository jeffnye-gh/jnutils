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
#include <iostream>
using namespace std;

vector<string> Mshell::helpVec = {
"=============================================================================",
" General commands",
"=============================================================================",
"  ? | ??      | help   : show help  ",
"  q | quit    | exit   : exit application ",
"  h | history          : show command history ",
"",
"  version              : Display the version info  ", 
"  rnotes               : Display the release notes", 
"  !<int>               : execute command <int> from the history list ", 
""
};
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
bool Mshell::shellShowHelp(bool)
{ 
  for(size_t i=0;i<helpVec.size();++i) out<<helpVec[i]<<endl;
  return true;
}
