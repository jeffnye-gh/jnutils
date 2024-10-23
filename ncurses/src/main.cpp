#include <ncurses.h>
#include <iostream>

#define MAIN_WIDTH 132
#define MAIN_HEIGHT 44

void init_windows(WINDOW **xregs_win, WINDOW **csrs_win, WINDOW **vars_win, 
                  WINDOW **wp_win, WINDOW **bp_win, 
                  WINDOW **dis_win, WINDOW **call_win,WINDOW **cmd_win,WINDOW **status_win);

void draw_borders(WINDOW *win, const char *label);
void resize_disassembly(WINDOW **dis_win, WINDOW **call_win,WINDOW **cmd_win, int new_height);
void draw_xregs_content(WINDOW *xregs_win);
void draw_csrs_content (WINDOW *csrs_win);
void draw_variables_content(WINDOW *vars_win);
void draw_watchpoint_content(WINDOW *wp_win);
void draw_breakpoint_content(WINDOW *bp_win);
void draw_disassembly_content(WINDOW *dis_win);
void draw_call_stack_content(WINDOW *call_win);
void draw_command_content(WINDOW *cmd_win);
void update_status_bar(WINDOW *status_win);

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();

    // Initialize color pair for black text on a white background
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    // Set the background color for the entire screen
    bkgd(COLOR_PAIR(1));
    refresh();

    int main_width = MAIN_WIDTH;
    int main_height = MAIN_HEIGHT;
    int dis_height = 12;
    int cmd_height = 6;
    int dis_y = main_height - dis_height - cmd_height - 3;

    WINDOW *xregs_win, *csrs_win, *vars_win, *wp_win, *bp_win, *dis_win, *call_win, *cmd_win, *status_win;

    init_windows(&xregs_win, &csrs_win, &vars_win, &wp_win, &bp_win, &dis_win, &call_win, &cmd_win,&status_win);
   
    draw_xregs_content(xregs_win);
    draw_csrs_content(csrs_win);
    draw_variables_content(vars_win);
    draw_watchpoint_content(wp_win);
    draw_breakpoint_content(bp_win);
    draw_disassembly_content(dis_win);
    draw_call_stack_content(call_win);
    draw_command_content(cmd_win);
    update_status_bar(status_win);

    // Main loop to process input
    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                if (dis_y > 5) {
                    dis_y--;
                    resize_disassembly(&dis_win, &call_win, &cmd_win, dis_y);
                }
                break;
            case KEY_DOWN:
                if (dis_y < main_height - 20) {
                    dis_y++;
                    resize_disassembly(&dis_win, &call_win, &cmd_win, dis_y);
                }
                break;
            default:
                break;
        }
    }

    // Cleanup
    delwin(xregs_win);
    delwin(csrs_win);
    delwin(vars_win);
    delwin(wp_win);
    delwin(bp_win);
    delwin(dis_win);
    delwin(call_win);
    delwin(cmd_win);
    endwin();

    return 0;
}

void draw_xregs_content(WINDOW *xregs_win) {
    // Clear the window's existing content
    wclear(xregs_win);

    // Redraw the borders and label for the window
    draw_borders(xregs_win, "XRegs");

    // Add text to the window at specific positions
    
    mvwprintw(xregs_win, 1, 2, "X0  0x123456789abcdef0 *");
    mvwprintw(xregs_win, 2, 2, "X1  0x123456789abcdef0 *");
    mvwprintw(xregs_win, 3, 2, "X2  0x123456789abcdef0 *");
    mvwprintw(xregs_win, 4, 2, "X3  0x123456789abcdef0 *");
    mvwprintw(xregs_win, 5, 2, "X4  0x123456789abcdef0 *");
    mvwprintw(xregs_win, 6, 2, "X5  0x123456789abcdef0 *");
    mvwprintw(xregs_win, 7, 2, "X6  0x123456789abcdef0 *");
    mvwprintw(xregs_win, 8, 2, "X7  0x123456789abcdef0 *");
    mvwprintw(xregs_win, 9, 2, "X8  0x123456789abcdef0 *");
    mvwprintw(xregs_win,10, 2, "X9  0x123456789abcdef0 *");
    mvwprintw(xregs_win,11, 2, "X10 0x123456789abcdef0 *");
    mvwprintw(xregs_win,12, 2, "X11 0x123456789abcdef0 *");
    mvwprintw(xregs_win,13, 2, "X12 0x123456789abcdef0 *");
    mvwprintw(xregs_win,14, 2, "X13 0x123456789abcdef0 *");
    mvwprintw(xregs_win,15, 2, "X14 0x123456789abcdef0 *");
    mvwprintw(xregs_win,16, 2, "X15 0x123456789abcdef0 *");

    mvwprintw(xregs_win, 1, 28, "X16 0x123456789abcdef0 *");
    mvwprintw(xregs_win, 2, 28, "X17 0x123456789abcdef0 *");
    mvwprintw(xregs_win, 3, 28, "X18 0x123456789abcdef0 *");
    mvwprintw(xregs_win, 4, 28, "X19 0x123456789abcdef0 *");
    mvwprintw(xregs_win, 5, 28, "X20 0x123456789abcdef0 *");
    mvwprintw(xregs_win, 6, 28, "X21 0x123456789abcdef0 *");
    mvwprintw(xregs_win, 7, 28, "X22 0x123456789abcdef0 *");
    mvwprintw(xregs_win, 8, 28, "X23 0x123456789abcdef0 *");
    mvwprintw(xregs_win, 9, 28, "X24 0x123456789abcdef0 *");
    mvwprintw(xregs_win,10, 28, "X25 0x123456789abcdef0 *");
    mvwprintw(xregs_win,11, 28, "X26 0x123456789abcdef0 *");
    mvwprintw(xregs_win,12, 28, "X27 0x123456789abcdef0 *");
    mvwprintw(xregs_win,13, 28, "X28 0x123456789abcdef0 *");
    mvwprintw(xregs_win,14, 28, "X29 0x123456789abcdef0 *");
    mvwprintw(xregs_win,15, 28, "X30 0x123456789abcdef0 *");
    mvwprintw(xregs_win,16, 28, "X31 0x123456789abcdef0 *");

    // Add more registers as needed...

    // Refresh the window to update the display
    wrefresh(xregs_win);
}

void draw_csrs_content(WINDOW *csrs_win) {
    wclear(csrs_win);
    draw_borders(csrs_win, "Csrs");
    mvwprintw(csrs_win, 1, 3,  "mstatus    0x123456789abcdef0 *    sip        0x123456789abcdef0 *");
    mvwprintw(csrs_win, 2, 3,  "misa       0x123456789abcdef0 *    fcsr       0x123456789abcdef0 *");
    mvwprintw(csrs_win, 3, 3,  "medeleg    0x123456789abcdef0 *    cycle      0x123456789abcdef0 *");
    mvwprintw(csrs_win, 4, 3,  "mideleg    0x123456789abcdef0 *    cycleh     0x123456789abcdef0 *");
    mvwprintw(csrs_win, 5, 3,  "mie        0x123456789abcdef0 *    time       0x123456789abcdef0 *");
    mvwprintw(csrs_win, 6, 3,  "mtvec      0x123456789abcdef0 *    timeh      0x123456789abcdef0 *");
    mvwprintw(csrs_win, 7, 3,  "mepc       0x123456789abcdef0 *    instret    0x123456789abcdef0 *");
    mvwprintw(csrs_win, 8, 3,  "mcause     0x123456789abcdef0 *    instreth   0x123456789abcdef0 *");
    mvwprintw(csrs_win, 9, 3,  "mtval      0x123456789abcdef0 *    mcycle     0x123456789abcdef0 *");
    mvwprintw(csrs_win,10, 3,  "mip        0x123456789abcdef0 *    minstret   0x123456789abcdef0 *");
    mvwprintw(csrs_win,11, 3,  "sstatus    0x123456789abcdef0 *    pmpcfg0    0x123456789abcdef0 *");
    mvwprintw(csrs_win,12, 3,  "sie        0x123456789abcdef0 *    pmpcfg1    0x123456789abcdef0 *");
    mvwprintw(csrs_win,13, 3,  "stvec      0x123456789abcdef0 *    pmpcfg0    0x123456789abcdef0 *");
    mvwprintw(csrs_win,14, 3,  "sepc       0x123456789abcdef0 *    csrXYZ     0x123456789abcdef0 *");
    mvwprintw(csrs_win,15, 3,  "scause     0x123456789abcdef0 *    csrXYZ     0x123456789abcdef0 *");
    mvwprintw(csrs_win,16, 3,  "stval      0x123456789abcdef0 *    csrXYZ     0x123456789abcdef0 *");

    wrefresh(csrs_win);
}

void draw_variables_content(WINDOW *vars_win) {
    wclear(vars_win);
    draw_borders(vars_win, "Variables");
    mvwprintw(vars_win, 1, 2, "my_uint32_t");
    mvwprintw(vars_win, 2,14, "* 0x12345678");

    mvwprintw(vars_win, 4, 2, "my_uint64_t");
    mvwprintw(vars_win, 5,14, "* 0x123456789abcdef0");

    mvwprintw(vars_win, 7, 2, "my_uint128_t");
    mvwprintw(vars_win, 8,14, "* 0x123456789abcdef0123456789abcdef0");

    mvwprintw(vars_win,10, 2, "a_long_variable_name");
    mvwprintw(vars_win,11,14, "* 0x123456789abcdef0123456789abcdef0");

    mvwprintw(vars_win,13, 2, "myclass::subclass::variable_name");
    mvwprintw(vars_win,14,14, "* 0x123456789abcdef0123456789abcdef0");
    wrefresh(vars_win);
}

void draw_watchpoint_content(WINDOW *wp_win) {
    wclear(wp_win);
    draw_borders(wp_win, "Watchpoints");
    mvwprintw(wp_win, 1, 2, " 0 0x0000000000000000 0x123456789abcdef0 *");
    mvwprintw(wp_win, 2, 2, " 1 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win, 3, 2, " 2 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win, 4, 2, " 3 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win, 5, 2, " 4 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win, 6, 2, " 5 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win, 7, 2, " 6 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win, 8, 2, " 7 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win, 9, 2, " 8 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win,10, 2, " 9 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win,11, 2, "10 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win,12, 2, "11 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win,13, 2, "12 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win,14, 2, "13 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win,15, 2, "14 0x0000000000000010 0x123456789abcdef0 -");
    mvwprintw(wp_win,16, 2, "15 0x0000000000000010 0x123456789abcdef0 -");

    wrefresh(wp_win);
}

void draw_breakpoint_content(WINDOW *bp_win) {
    wclear(bp_win);
    draw_borders(bp_win, "Breakpoints");
    mvwprintw(bp_win, 1, 2, " 0 A 0x0000000000000000 * ");
    mvwprintw(bp_win, 2, 2, " 1 D 0x0000000000000000 - ");
    mvwprintw(bp_win, 3, 2, " 2 A 0x0000000000000000 - ");
    mvwprintw(bp_win, 4, 2, " 3 D 0x0000000000000000 - ");
    mvwprintw(bp_win, 5, 2, " 4 A 0x0000000000000000 - ");
    mvwprintw(bp_win, 6, 2, " 5 D 0x0000000000000000 - ");
    mvwprintw(bp_win, 7, 2, " 6 D 0x0000000000000000 - ");
    mvwprintw(bp_win, 8, 2, " 7 D 0x0000000000000010 - ");
    mvwprintw(bp_win, 9, 2, " 8 D 0x0000000000000010 - ");
    mvwprintw(bp_win,10, 2, " 9 D 0x0000000000000010 - ");
    mvwprintw(bp_win,11, 2, "10 D 0x0000000000000010 - ");
    mvwprintw(bp_win,12, 2, "11 D 0x0000000000000010 - ");
    mvwprintw(bp_win,13, 2, "12 D 0x0000000000000010 - ");
    mvwprintw(bp_win,14, 2, "13 D 0x0000000000000010 - ");
    mvwprintw(bp_win,15, 2, "14 D 0x0000000000000010 - ");
    mvwprintw(bp_win,16, 2, "15 D 0x0000000000000010 - ");

    wrefresh(bp_win);
}

void draw_disassembly_content(WINDOW *dis_win) 
{
    wclear(dis_win);
    draw_borders(dis_win, "Disassembly");
    mvwprintw(dis_win, 1, 2, "000000000800008c <foo>:");
    mvwprintw(dis_win, 2, 2, "  00000000800008c: ff010113  addi sp,sp,-16");
    mvwprintw(dis_win, 3, 2, "  000000008000090: 00112623  sw   ra,12(sp)");
    mvwprintw(dis_win, 4, 2, "  000000008000094: 00812423  sw   s0,8(sp)");
    mvwprintw(dis_win, 5, 2, "  000000008000098: 00912223  sw   a0,4(sp)");
    mvwprintw(dis_win, 6, 2, "  00000000800009c: 00050413  mv   s0,sp");
    mvwprintw(dis_win, 7, 2, "  0000000080000a0: 00040513  li   a0,0 ");
    mvwprintw(dis_win, 8, 2, "  0000000080000a4: 00c12083  lw   ra,12(sp)");
    mvwprintw(dis_win, 9, 2, "  0000000080000a8: 00812403  lw   s0,8(sp)");
    mvwprintw(dis_win,10, 2, "  0000000080000ac: 01010113  addi sp,sp,16");

    wrefresh(dis_win);
}

void draw_call_stack_content(WINDOW *call_win) {
    wclear(call_win);
    draw_borders(call_win, "Call Stack");
    mvwprintw(call_win,1,2, "#0  main () at main.cpp:15");
    mvwprintw(call_win,2,2, "#1  0x0000000000010020 in foo (x=42) at foo.cpp:8");
    mvwprintw(call_win,3,2, "#2  0x0000000000010044 in bar (y=13) at bar.cpp:20");
    mvwprintw(call_win,4,2, "#3  0x0000000000010068 in baz () at baz.cpp:5");
    wrefresh(call_win);
}

void draw_command_content(WINDOW *cmd_win) {
    wclear(cmd_win);
    draw_borders(cmd_win, "Command");
    mvwprintw(cmd_win,2, 2,"asio> csrc asio.sh");
    mvwprintw(cmd_win,3, 2,"-I: Help message");
    mvwprintw(cmd_win,4, 2,"asio> help");
    mvwprintw(cmd_win,5, 2,"-I: Help message");
    mvwprintw(cmd_win,6, 2,"asio> info regs");
    mvwprintw(cmd_win,7, 2,"-I: INFO_REGS data received: X0:0x0000000000000000:X1:0x0000234987234000:X2:0xaaabdbdbd3434340");
    mvwprintw(cmd_win,8, 2,"asio>");
    mvwprintw(cmd_win,9, 2,"asio>");

    wrefresh(cmd_win);
}

void update_status_bar(WINDOW *status_win) 
{
    wclear(status_win);
    (status_win, 1, 2, "STATUS: connected to server 127.0.0.1:12345");
}

// newwin(int height, int width, int starty, int startx);

void init_windows(WINDOW **xregs_win, WINDOW **csrs_win, WINDOW **vars_win,
                  WINDOW **wp_win, WINDOW **bp_win, 
                  WINDOW **dis_win, WINDOW **call_win, WINDOW **cmd_win,WINDOW **status_win)
{
    // Top section windows: XRegs and Csrs
    *xregs_win = newwin(18, 55, 0, 1);
    wbkgd(*xregs_win, COLOR_PAIR(1));
    draw_borders(*xregs_win, "XRegs");

    *csrs_win = newwin(18, 75, 0, 56);
    wbkgd(*csrs_win, COLOR_PAIR(1));
    draw_borders(*csrs_win, "Csrs");

    // Middle section: Breakpoints, Watchpoints, User Vars, Server Status/Future Expansion
    *bp_win = newwin(18, 30, 18, 1); // Breakpoints on the left
    wbkgd(*bp_win, COLOR_PAIR(1));
    draw_borders(*bp_win, "Breakpoints");

    *wp_win = newwin(18, 46, 18, 31); // Watchpoints next to Breakpoints
    wbkgd(*wp_win, COLOR_PAIR(1));
    draw_borders(*wp_win, "Watchpoints");

    *vars_win = newwin(18, 54, 18, 77); // User Vars next to Watchpoints
    wbkgd(*vars_win, COLOR_PAIR(1));
    draw_borders(*vars_win, "Variables");

    // Bottom section windows: Disassembly and Command Window
    *dis_win = newwin(12, 65, 36, 1);
    wbkgd(*dis_win, COLOR_PAIR(1));
    draw_borders(*dis_win, "Disassembly Window");

    *call_win = newwin(12, 65, 36, 66);
    wbkgd(*call_win, COLOR_PAIR(1));
    draw_borders(*call_win, "Call Stack");

    *cmd_win = newwin(11, 130, 48, 1);
    wbkgd(*cmd_win, COLOR_PAIR(1));
    draw_borders(*cmd_win, "Command Window");

    *status_win = newwin(1, 130, 59, 1);
    wbkgd(*status_win, COLOR_PAIR(1));
    wprintw(*status_win, "Status: Ready");
    wrefresh(*status_win);
}

void draw_borders(WINDOW *win, const char *label) {
    box(win, 0, 0);
    // Add the label at the top left corner of the window
    mvwprintw(win, 0, 2, "[ %s ]", label);
    wrefresh(win);
}

void resize_disassembly(WINDOW **dis_win, WINDOW **call_win,WINDOW **cmd_win, int new_height) {
    int y, x;
    getmaxyx(stdscr, y, x);

    delwin(*dis_win);
    delwin(*cmd_win);
    delwin(*call_win);

    *dis_win = newwin(new_height, x - 2, 1, 1);
    wbkgd(*dis_win, COLOR_PAIR(1));

    *call_win = newwin(new_height, x - 2, 1, 1);
    wbkgd(*call_win, COLOR_PAIR(1));

    *cmd_win = newwin(y - new_height - 1, x - 2, new_height + 1, 1);
    wbkgd(*cmd_win, COLOR_PAIR(1));

    draw_borders(*dis_win, "Disassembly Window");
    draw_borders(*call_win, "Call Stack");
    draw_borders(*cmd_win, "Command Window");
}

