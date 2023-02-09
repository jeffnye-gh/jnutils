// --------------------------------------------------------------------
// Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
#pragma once
#include "options.h"

struct Test
{
  Test(int,int);
  void query_options();

  int var_a{1};
  int var_b{2};
};
