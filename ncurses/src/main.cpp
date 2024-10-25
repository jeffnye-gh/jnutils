// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "jndbg.h"
#include <iostream>

int main() {
    Jndbg dbgr;
    dbgr.init();

    dbgr.addFileWatcher(Jndbg::XREGS_WATCH_FILE,
                        std::bind(&Jndbg::onXregsFileChanged, &dbgr));
    dbgr.addFileWatcher(Jndbg::CSRS_WATCH_FILE,
                        std::bind(&Jndbg::onCsrsFileChanged, &dbgr));
    dbgr.addFileWatcher(Jndbg::EXE_WATCH_FILE,
                        std::bind(&Jndbg::onExecutionFileChanged, &dbgr));

    dbgr.startFileWatchers();
    dbgr.mainLoop();
    dbgr.cleanup();

    return 0;
}

