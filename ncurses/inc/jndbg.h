// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#pragma once
#include "fieldinfo.h"

#include <ncurses.h>
#include <string>
#include <vector>
#include <map>

struct Jndbg
{
  Jndbg(int width = 132, int height = 60);
  ~Jndbg();

  void init();
  void mainLoop();
  void cleanup();

private:
  int main_width;
  int main_height;
  int dis_height;
  int cmd_height;
  int dis_y;

  WINDOW *xregs_win;
  WINDOW *csrs_win;
  WINDOW *vars_win;
  WINDOW *wp_win;
  WINDOW *bp_win;
  WINDOW *dis_win;
  WINDOW *call_win;
  WINDOW *cmd_win;
  WINDOW *status_win;

  void initWindows();
  void drawBorders(WINDOW *win, const std::string &label);
  void resizeDisassembly(int new_height);

  void initFields();
  void initXregFields();
  void initCsrFields();
  void initVariablesFields();
  void initWatchpointFields();
  void initBreakpointFields();
  void initDisassemblyFields();
  void initCallStackFields();
  void initCommandFields();
  void initStatusBarFields();

  void initContent();
  void drawXregsContent();
  void drawCsrsContent();
  void drawVariablesContent();
  void drawWatchpointContent();
  void drawBreakpointContent();
  void drawDisassemblyContent();
  void drawCallStackContent();
  void drawCommandContent();
  void updateStatusBar();

  bool is_init{false};

  std::map<std::string,XregFieldInfo>     xregs;
  std::map<std::string,CsrFieldInfo>      csrs;
  std::map<uint32_t,BreakPointFieldInfo>  breakpoints;
  std::map<uint32_t,WatchPointFieldInfo>  watchpoints;
  std::map<uint32_t,VariablesFieldInfo>   variables;
  std::map<uint32_t,DisassemblyFieldInfo> disassembly;
  std::map<uint32_t,CallStackFieldInfo>   callstack;
  std::map<uint32_t,CommandFieldInfo>     command;
  std::vector<StatusFieldInfo> status;

  static const std::map<uint32_t,std::string> example_disassembly;
  static const std::map<std::string,std::pair<std::string,std::string> >
                                                             example_variables;
  static const std::map<uint32_t,std::string> example_callstack;
  static const std::map<uint32_t,std::string> example_commands;
  static std::map<std::string,std::string> example_status;

  static constexpr uint32_t XREGS_W_x = 1;
  static constexpr uint32_t XREGS_W_y = 0;
  static constexpr uint32_t XREGS_W_h = 18;
  static constexpr uint32_t XREGS_W_w = 55;

  static constexpr uint32_t CSRS_W_x  = 56;
  static constexpr uint32_t CSRS_W_y  = 0;
  static constexpr uint32_t CSRS_W_h  = 18;
  static constexpr uint32_t CSRS_W_w  = 75;

  static constexpr uint32_t BPS_W_x   = 1;
  static constexpr uint32_t BPS_W_y   = 18;
  static constexpr uint32_t BPS_W_h   = 18;
  static constexpr uint32_t BPS_W_w   = 30;

  static constexpr uint32_t WPS_W_x   = 31;
  static constexpr uint32_t WPS_W_y   = 18;
  static constexpr uint32_t WPS_W_h   = 18;
  static constexpr uint32_t WPS_W_w   = 48;

  static constexpr uint32_t VARS_W_x  = 79;
  static constexpr uint32_t VARS_W_y  = 18;
  static constexpr uint32_t VARS_W_h  = 18;
  static constexpr uint32_t VARS_W_w  = 52;

  static constexpr uint32_t DIS_W_x   = 1;
  static constexpr uint32_t DIS_W_y   = 36;
  static constexpr uint32_t DIS_W_h   = 12;
  static constexpr uint32_t DIS_W_w   = 65;

  static constexpr uint32_t CALL_W_x  = 66;
  static constexpr uint32_t CALL_W_y  = 36;
  static constexpr uint32_t CALL_W_h  = 12;
  static constexpr uint32_t CALL_W_w  = 65;

  static constexpr uint32_t CMD_W_x   = 1;
  static constexpr uint32_t CMD_W_y   = 48;
  static constexpr uint32_t CMD_W_h   = 11;
  static constexpr uint32_t CMD_W_w   = 130;

  static constexpr uint32_t STAT_W_x   = 1;
  static constexpr uint32_t STAT_W_y   = 59;
  static constexpr uint32_t STAT_W_h   = 1;
  static constexpr uint32_t STAT_W_w   = 130;

};

