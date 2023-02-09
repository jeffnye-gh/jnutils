// --------------------------------------------------------------------
// Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
#include "options.h"
#include "test.h"
using namespace std;
Test::Test(int _a,int _b) : var_a(_a), var_b(_b) { }

void Test::query_options() 
{
  opts->query_options();
}
