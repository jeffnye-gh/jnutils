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
