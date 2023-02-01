#include "mshell.h"

using namespace std;
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Mshell::emsg(uint32_t err)
{
  switch(err)
  {
    case NO_ERR: return;
    case SYNTAX_ERROR:
      if(ncursesEnable)
        emsg(string("Unknown command: '")+lineBuffer+string("'"));
      else 
      {
        emsg("Syntax error");
        emsg(errText);
      }
      return;
    case EVENT_NOT_FOUND: emsg("Event not found"); return;
    default:              emsg("Unknown error");   return;
  }
}
