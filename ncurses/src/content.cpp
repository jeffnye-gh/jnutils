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

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Jndbg::drawCallStackContent() {
  if(is_init) {
    wclear(call_win);
    drawBorders(call_win, "Call Stack");
  }

  for(auto &[key,fi] : callstack) {
    stringstream ss;
    ss << setw(2)<<fi.label;
    string label = ss.str()+"#";
    mvwprintw(call_win,fi.label_y, fi.label_x, "%s", label.c_str());
    mvwprintw(call_win,fi.data_y,  fi.data_x,  "%s", fi.data.c_str());
  }

  wrefresh(call_win);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Jndbg::drawCommandContent() {
  if(is_init) {
    wclear(cmd_win);
    drawBorders(cmd_win, "Command");
  }

  for(auto &[key,fi] : command) {
    mvwprintw(cmd_win,fi.data_y,fi.data_x,"%s", fi.data.c_str());
  }

  wrefresh(cmd_win);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Jndbg::updateStatusBar() {
  wclear(status_win);

  int height, width;
  getmaxyx(status_win,height,width);

  width -= 2; //border
  uint32_t ypos = StatusFieldInfo::STAT_y;

  for(auto &fi : status) {

    mvwhline(status_win, ypos, 0, ' ', width); //clear
    wmove(status_win, ypos, 0);

    string msg = "STATUS: "+fi.msg;
    size_t flags_x = width - fi.flags.length();

    mvwprintw(status_win,ypos,StatusFieldInfo::STAT_Msg_x,"%s", msg.c_str());
    mvwprintw(status_win,ypos,flags_x,       "%s", fi.flags.c_str());
    wmove(status_win, ypos, 0);
    wrefresh(status_win);
  }

  wrefresh(status_win);
}

