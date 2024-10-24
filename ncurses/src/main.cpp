// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "jndbg.h"

int main() {
  Jndbg dbgr;
  dbgr.init();
  dbgr.mainLoop();
  dbgr.cleanup();
  return 0;
}

