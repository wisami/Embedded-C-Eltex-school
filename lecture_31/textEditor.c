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

        while ((mvwinch(wnd, y, --x) & A_CHARTEXT) == ' ' && x != 0)
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

void open_file(WINDOW *wnd, char *path) {

    const int size_name = 1024;
    int index = 0;
    char name[size_name];
    char ch;

    if (path != NULL) {
        return;
    }
    else {

        wprintw(wnd, "Enter name file:");
        wrefresh(wnd);

        while (ch = wgetch(wnd) != KEY_ENTER && index < size_name) {
            wprintw(wnd, "%c", ch);
            wrefresh(wnd);
            name[index++] = ch;
        }
    }
}

void save(WINDOW *wnd) {

    FILE *fd;
    int rows, cols;
    getmaxyx(wnd, rows, cols);
    char text[rows][cols + 1];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            text[i][j] = (mvwinch(wnd, i, j) & A_CHARTEXT);
        }
        text[i][cols] = '\0';
    }

    fd = fopen("text", "w");
    for (int i = 0; i < rows; i++)
        fprintf(fd, "%s\n", text[i]);
    fclose(fd);

}