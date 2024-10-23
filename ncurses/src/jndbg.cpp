#include "jndbg.h"
#include <iostream>

using namespace std;

Jndbg::Jndbg(int width, int height)
    : main_width(width), main_height(height), dis_height(12), cmd_height(6),
      dis_y(height - dis_height - cmd_height - 3),
      xregs_win(nullptr), csrs_win(nullptr), vars_win(nullptr),
      wp_win(nullptr), bp_win(nullptr), dis_win(nullptr), 
      call_win(nullptr), cmd_win(nullptr), status_win(nullptr) {}

Jndbg::~Jndbg() {
    cleanup();
}

void Jndbg::init() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    bkgd(COLOR_PAIR(1));
    refresh();
    initWindows();
    initFields();
    //initContent();
}

void Jndbg::initWindows() {
    xregs_win = newwin(18, 55, 0, 1);
    wbkgd(xregs_win, COLOR_PAIR(1));
    drawBorders(xregs_win, "XRegs");

    csrs_win = newwin(18, 75, 0, 56);
    wbkgd(csrs_win, COLOR_PAIR(1));
    drawBorders(csrs_win, "Csrs");

    bp_win = newwin(18, 30, 18, 1);
    wbkgd(bp_win, COLOR_PAIR(1));
    drawBorders(bp_win, "Breakpoints");

    wp_win = newwin(18, 46, 18, 31);
    wbkgd(wp_win, COLOR_PAIR(1));
    drawBorders(wp_win, "Watchpoints");

    vars_win = newwin(18, 54, 18, 77);
    wbkgd(vars_win, COLOR_PAIR(1));
    drawBorders(vars_win, "Variables");

    dis_win = newwin(12, 65, 36, 1);
    wbkgd(dis_win, COLOR_PAIR(1));
    drawBorders(dis_win, "Disassembly");

    call_win = newwin(12, 65, 36, 66);
    wbkgd(call_win, COLOR_PAIR(1));
    drawBorders(call_win, "Call Stack");

    cmd_win = newwin(11, 130, 48, 1);
    wbkgd(cmd_win, COLOR_PAIR(1));
    drawBorders(cmd_win, "Command");

    status_win = newwin(1, 130, 59, 1);
    wbkgd(status_win, COLOR_PAIR(1));
    wprintw(status_win, "Status: Ready");
    wrefresh(status_win);

    is_init = true;
    drawXregsContent();
    drawCsrsContent();
    drawVariablesContent();
    drawWatchpointContent();
    drawBreakpointContent();
    drawDisassemblyContent();
    drawCallStackContent();
    drawCommandContent();
    updateStatusBar();
    is_init = false;
}

void Jndbg::drawBorders(WINDOW *win, const std::string &label) {
    box(win, 0, 0);
    mvwprintw(win, 0, 2, "[ %s ]", label.c_str());
    wrefresh(win);
}

void Jndbg::mainLoop() {
    drawXregsContent();
    drawCsrsContent();
    drawVariablesContent();
    drawWatchpointContent();
    drawBreakpointContent();
    drawDisassemblyContent();
    drawCallStackContent();
    drawCommandContent();
    updateStatusBar();

    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                if (dis_y > 5) {
                    dis_y--;
                    resizeDisassembly(dis_y);
                }
                break;
            case KEY_DOWN:
                if (dis_y < main_height - 20) {
                    dis_y++;
                    resizeDisassembly(dis_y);
                }
                break;
            default:
                break;
        }
    }
}

void Jndbg::cleanup() {
    delwin(xregs_win);
    delwin(csrs_win);
    delwin(vars_win);
    delwin(wp_win);
    delwin(bp_win);
    delwin(dis_win);
    delwin(call_win);
    delwin(cmd_win);
    delwin(status_win);
    endwin();
}

void Jndbg::resizeDisassembly(int new_height) {
    int y, x;
    getmaxyx(stdscr, y, x);

    delwin(dis_win);
    delwin(cmd_win);
    delwin(call_win);

    dis_win = newwin(new_height, x - 2, 1, 1);
    wbkgd(dis_win, COLOR_PAIR(1));
    call_win = newwin(new_height, x - 2, 1, 1);
    wbkgd(call_win, COLOR_PAIR(1));
    cmd_win = newwin(y - new_height - 1, x - 2, new_height + 1, 1);
    wbkgd(cmd_win, COLOR_PAIR(1));

    drawBorders(dis_win, "Disassembly");
    drawBorders(call_win, "Call Stack");
    drawBorders(cmd_win, "Command");
}

