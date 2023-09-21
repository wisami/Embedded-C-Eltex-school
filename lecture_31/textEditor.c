#include <ncurses.h>
#include <stdlib.h>

void mmove(WINDOW *wnd, int ny, int nx) {

    int y, x;

    getyx(wnd, y, x);
    wmove(wnd, y + ny, x + nx);
    wrefresh(wnd);
}

void backspace(WINDOW *wnd) {

    int y, x;
    char ch;

    getyx(wnd, y, x);

    if (x == 0 && y != 0) {

        x = getmaxx(wnd) - 1;
        y--;

        while (mvwinch(wnd, y, --x) == ' ' && x != 0)
            continue;

        wmove(wnd, y, ++x);
        wrefresh(wnd);
    }
    else {
        mvwaddch(wnd, y, x - 1, ' ');
        wrefresh(wnd);
        wmove(wnd, y, x - 1);
    }

}

void save(WINDOW *wnd) {

    FILE *fd;
    int rows, cols;
    getmaxyx(wnd, rows, cols);
    rows -= 1; cols -= 1;
    char text[rows][cols];

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            text[i - 1][j - 1] = mvwinch(wnd, i, j);
        }
    }

    fd = fopen("text", "w");
    for (int i = 0; i < rows; i++)
        fprintf(fd, "%s\n", text[i]);
    fclose(fd);

}