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
};

