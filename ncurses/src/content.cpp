#include "jndbg.h"
#include <iostream>

using namespace std;
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Jndbg::drawXregsContent() {
  if(is_init) {
    wclear(xregs_win);
    drawBorders(xregs_win, "XRegs");
  }

  for(auto &[key,fi] : xregs) {
    mvwprintw(xregs_win, fi.label_y,  fi.label_x, "%s", fi.label.c_str());
    mvwprintw(xregs_win, fi.data_y,   fi.data_x,  "%s", fi.data.c_str());
    mvwprintw(xregs_win, fi.active_y, fi.active_x,"%s", fi.active.c_str());
  }

  wrefresh(xregs_win);

}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Jndbg::drawCsrsContent() {
  if(is_init) {
    wclear(csrs_win);
    drawBorders(csrs_win, "Csrs");
  }

  for(auto &[key,fi] : csrs) {
    mvwprintw(csrs_win, fi.label_y,  fi.label_x, "%s", fi.label.c_str());
    mvwprintw(csrs_win, fi.data_y,   fi.data_x,  "%s", fi.data.c_str());
    mvwprintw(csrs_win, fi.active_y, fi.active_x,"%s", fi.active.c_str());

  }

  wrefresh(csrs_win);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Jndbg::drawBreakpointContent() {
  if(is_init) {
    wclear(bp_win);
    drawBorders(bp_win, "Breakpoints");
  }

  for(auto &[key,fi] : breakpoints) {
    mvwprintw(bp_win, fi.label_y,  fi.label_x, "%s", fi.label.c_str());
    mvwprintw(bp_win, fi.enable_y, fi.enable_x,"%s", fi.enable.c_str());
    mvwprintw(bp_win, fi.data_y,   fi.data_x,  "%s", fi.data.c_str());
    mvwprintw(bp_win, fi.active_y, fi.active_x,"%s", fi.active.c_str());
  }
  
  wrefresh(bp_win);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Jndbg::drawWatchpointContent() {
  if(is_init) {
    wclear(wp_win);
    drawBorders(wp_win, "Watchpoints");
  }

  for(auto &[key,fi] : watchpoints) {
    mvwprintw(wp_win, fi.label_y,  fi.label_x, "%s", fi.label.c_str());
    mvwprintw(wp_win, fi.enable_y, fi.enable_x,"%s", fi.enable.c_str());
    mvwprintw(wp_win, fi.addr_y,   fi.addr_x,  "%s", fi.addr.c_str());
    mvwprintw(wp_win, fi.data_y,   fi.data_x,  "%s", fi.data.c_str());
    mvwprintw(wp_win, fi.active_y, fi.active_x,"%s", fi.active.c_str());
  }

  wrefresh(wp_win);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Jndbg::drawVariablesContent() {
    wclear(vars_win);
    drawBorders(vars_win, "Variables");
    mvwprintw(vars_win, 1, 2, "my_uint32_t * 0x12345678");
    // Add more variables...
    wrefresh(vars_win);
}

const vector<string> Jndbg::example_disasm = {
"800040ca: d9258593      addi  x11, x11, -0x26e",
"800040ce: 467d          c.li  x12, 0x1f",
"800040d0: 0a9000ef      jal x1, 0x80004978 <memcpy>",
"800040d4: 00001517      auipc x10, 0x1",
"800040d8: d4c53983      ld  x19, -0x2b4(x10)",
"800040dc: 00001517      auipc x10, 0x1",
"800040e0: d4c53a03      ld  x20, -0x2b4(x10)",
"800040e4: 00001517      auipc x10, 0x1",
"800040e8: d4c53503      ld  x10, -0x2b4(x10)",
"800040ec: e9ce          c.sdsp  x19, 0xd0(x2)",
"800040ee: edd2          c.sdsp  x20, 0xd8(x2)",
"800040f0: f1aa          c.sdsp  x10, 0xe0(x2)",
"800040f2: 49525537      lui x10, 0x49525",
"800040f6: 45350a93      addi  x21, x10, 0x453",
"800040fa: d5d6          c.swsp  x21, 0xe8(x2)",
"800040fc: 6511          c.lui x10, 0x4",
"800040fe: 74e50c13      addi  x24, x10, 0x74e",
"80004102: 0f811623      sh  x24, 0xec(x2)",
"80004106: 0e010723      sb  x0, 0xee(x2)",
"8000410a: 00002517      auipc x10, 0x2",
"8000410e: 45a9          c.li  x11, 0xa",
"80004110: 94b52523      sw  x11, -0x6b6(x10)",
"80004114: 00001517      auipc x10, 0x1",
"80004118: 26a50413      addi  x8, x10, 0x26a",
"8000411c: 8522          c.mv  x10, x8",
"8000411e: 38d000ef      jal x1, 0x80004caa <CONDOR_PRINTF>",
"80004122: 00001517      auipc x10, 0x1",
"80004126: d7450513      addi  x10, x10, -0x28c",
"8000412a: 381000ef      jal x1, 0x80004caa <CONDOR_PRINTF>",
"8000412e: 8522          c.mv  x10, x8",
"80004130: 37b000ef      jal x1, 0x80004caa <CONDOR_PRINTF>",
"80004134: d901a503      lw  x10, -0x270(x3)",
"80004138: c511          c.beqz  x10, 0x80004144 <main+0xba>",
"8000413a: 00001517      auipc x10, 0x1",
"8000413e: d8c50513      addi  x10, x10, -0x274",
"80004142: a029          c.j 0x8000414c <main+0xc2>",
"80004144: 00001517      auipc x10, 0x1",
"80004148: dae50513      addi  x10, x10, -0x252",
"8000414c: 35f000ef      jal x1, 0x80004caa <CONDOR_PRINTF>",
"80004150: 8522          c.mv  x10, x8",
"80004152: 359000ef      jal x1, 0x80004caa <CONDOR_PRINTF>",
"80004156: 00001517      auipc x10, 0x1",
"8000415a: dcb50513      addi  x10, x10, -0x235"
};

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Jndbg::drawDisassemblyContent() {
  if(is_init) {
    wclear(dis_win);
    drawBorders(dis_win, "Disassembly");
  }

  uint32_t xpos = DisasmblyFieldInfo::DIS_x;

  for(size_t i=0;i<10;++i) {
    uint32_t ypos = DisasmblyFieldInfo::DIS_y+i;
    mvwprintw(dis_win,ypos, xpos,"%s", example_disasm[i].c_str());
  }
    // Add more disassembly...
    wrefresh(dis_win);
}

void Jndbg::drawCallStackContent() {
    wclear(call_win);
    drawBorders(call_win, "Call Stack");
    mvwprintw(call_win, 1, 2, "#0 main () at main.cpp:15");
    // Add more call stack...
    wrefresh(call_win);
}

void Jndbg::drawCommandContent() {
    wclear(cmd_win);
    drawBorders(cmd_win, "Command");
    mvwprintw(cmd_win, 2, 2, "asio> help");
    // Add more commands...
    wrefresh(cmd_win);
}

void Jndbg::updateStatusBar() {
    wclear(status_win);
    mvwprintw(status_win, 0, 2, "STATUS: Connected to server 127.0.0.1:12345");
    wrefresh(status_win);
}

