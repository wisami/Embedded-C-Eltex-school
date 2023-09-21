#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <fcntl.h>
#include <locale.h>
#include "textEditor.h"

void sig_winch(int signo) {
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
}

int main(void) {
   
    WINDOW *wnd;
    WINDOW *subwnd;
    WINDOW *optwnd; 
    wchar_t ch;

    int rows, cols;

    initscr();
    signal(SIGWINCH, sig_winch);
    
    getmaxyx(stdscr, rows, cols);

    start_color();
    refresh();

    wnd = newwin(rows - 1, cols, 0, 0);
    box(wnd, '|', '-');
    wrefresh(wnd);
    subwnd = derwin(wnd, rows - 3, cols - 2, 1, 1);

    optwnd = newwin(1, cols, rows - 1, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    wbkgd(optwnd, COLOR_PAIR(1));
    wprintw(optwnd, "F1:Open; F2:Save; F3:Close;");
    wrefresh(optwnd);

    raw();
    noecho();
    keypad(subwnd, TRUE);

    while (1) {

        switch (ch = wgetch(subwnd)) {

            case KEY_UP:
                mmove(subwnd, -1, 0);
                break;

            case KEY_DOWN:
                mmove(subwnd, 1, 0);
                break;

            case KEY_LEFT:
                mmove(subwnd, 0, -1);
                break;

            case KEY_RIGHT:
                mmove(subwnd, 0, 1);
                break;

            case KEY_BACKSPACE:
                backspace(subwnd);
                break;

            case KEY_ENTER:
                wprintw(subwnd, "\n");
                break;

            case KEY_F(1):
                wprintw(subwnd, "F1");
                break;

            case KEY_F(2):
                save(wnd);
                break;

            case KEY_F(3):
                delwin(wnd);
                delwin(subwnd);
                delwin(optwnd);   
                endwin();
                exit(EXIT_SUCCESS);

            default:
                wprintw(subwnd, "%c", ch);
        }

    }

    delwin(wnd);
    delwin(subwnd);
    delwin(optwnd);   
    endwin();

    return 0;
}
