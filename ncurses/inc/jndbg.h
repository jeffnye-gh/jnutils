#pragma once
#include "fieldinfo.h"

#include <ncurses.h>
#include <string>
#include <map>

//struct FieldInfo {
//  FieldInfo(size_t s=64) 
//    : is_uninit(true),
//      is_inactive(true),
//      size(s),
//      label("???"),
//      data(size == 32 ? uninit32 : uninit64),
//      active(inactive)
//  {}
//
//  bool is_uninit;
//  bool is_inactive;
//
//  size_t size;
//  std::string label;
//  std::string data;
//  std::string active;
//
//  static constexpr std::string uninit64{"0x----------------"};
//  static constexpr std::string uninit32{"0x--------"};
//  static constexpr std::string inactive{"-"};
//
//};
//
//struct XregFieldInfo : public FieldInfo
//{
//  XregFieldInfo() : FieldInfo() {}
//  uint32_t label_x;
//  uint32_t label_y;
//  uint32_t data_x;
//  uint32_t data_y;
//  uint32_t active_x;
//  uint32_t active_y;
//  std::string active;
//};


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

  std::map<std::string,XregFieldInfo>       xregs;
  std::map<std::string,CsrFieldInfo>        csrs;
  std::map<uint32_t,BreakPointFieldInfo> breakpoints;
  std::map<uint32_t,WatchPointFieldInfo> watchpoints;

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

