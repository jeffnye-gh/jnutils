
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
