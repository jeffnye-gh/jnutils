// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "jndbg.h"

int main() {
    // Create an instance of Jndbg with default dimensions
    Jndbg dbgr;

    // Initialize the dbgr (set up ncurses and windows)
    dbgr.init();

    // Run the main loop (wait for user input and update the UI)
    dbgr.mainLoop();

    // Clean up resources before exiting
    dbgr.cleanup();

    return 0;
}

