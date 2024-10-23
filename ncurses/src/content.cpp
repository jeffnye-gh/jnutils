#include "jndbg.h"
#include <iostream>

using namespace std;

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
void Jndbg::drawBreakpointContent() {
  if(is_init) {
    wclear(bp_win);
  }

  drawBorders(bp_win, "Breakpoints");

  for(auto &[key,fi] : breakpoints) {
    mvwprintw(bp_win, fi.label_y,  fi.label_x, "%s", fi.label.c_str());
    mvwprintw(bp_win, fi.enable_y, fi.enable_x,"%s", fi.enable.c_str());
    mvwprintw(bp_win, fi.data_y,   fi.data_x,  "%s", fi.data.c_str());
    mvwprintw(bp_win, fi.active_y, fi.active_x,"%s", fi.active.c_str());
  }
  
 
  wrefresh(bp_win);
}


void Jndbg::drawVariablesContent() {
    wclear(vars_win);
    drawBorders(vars_win, "Variables");
    mvwprintw(vars_win, 1, 2, "my_uint32_t * 0x12345678");
    // Add more variables...
    wrefresh(vars_win);
}

void Jndbg::drawWatchpointContent() {
    wclear(wp_win);
    drawBorders(wp_win, "Watchpoints");
    mvwprintw(wp_win, 1, 2, "0 0x00000000 0x12345678");
    // Add more watchpoints...
    wrefresh(wp_win);
}

void Jndbg::drawDisassemblyContent() {
    wclear(dis_win);
    drawBorders(dis_win, "Disassembly");
    mvwprintw(dis_win, 1, 2, "00000000 <foo>:");
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

