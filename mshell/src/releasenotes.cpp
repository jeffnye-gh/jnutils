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
#include "mshell.h"

#include <iostream>
using namespace std;
// ----------------------------------------------------------------
// ----------------------------------------------------------------
vector<string> Mshell::relNotesVec = {
"MSHELL RELEASE NOTES",
"  -Changes for version 0.2.0",
"    * tcp support",
"  -Changes for version 0.1.0",
"    * 1st version",
""
};
// ----------------------------------------------------------------
// ----------------------------------------------------------------
bool Mshell::shellShowReleaseNotes(void)
{
  for(size_t i=0;i<relNotesVec.size();++i) cout<<relNotesVec[i]<<endl;
  return true;
}
