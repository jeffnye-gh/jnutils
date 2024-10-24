// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "jndbg.h"
#include <iostream>
#include <iomanip>

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
void Jndbg::drawVariablesContent() {
  if(is_init) {
    wclear(vars_win);
    drawBorders(vars_win, "Variables");
  }

  for(auto &[key,fi] : variables) {
    mvwprintw(vars_win, fi.label_y,  fi.label_x, "%s", fi.label.c_str());
    mvwprintw(vars_win, fi.active_y, fi.active_x,"%s", fi.active.c_str());
    mvwprintw(vars_win, fi.data_y,   fi.data_x,  "%s", fi.data.c_str());
  }

  wrefresh(vars_win);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Jndbg::drawDisassemblyContent() {
  if(is_init) {
    wclear(dis_win);
    drawBorders(dis_win, "Disassembly");
  }

  for(auto &[key,fi] : disassembly) {
    stringstream ss;
    ss << setw(8)<<hex<<fi.label;
    string label = "0x"+ss.str();
    mvwprintw(dis_win,fi.label_y, fi.label_x, "%s", label.c_str());
    mvwprintw(dis_win,fi.data_y,  fi.data_x,  "%s", fi.data.c_str());
  }

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

