#ifndef _TEXTEDITOR_H_
#define _TEXTEDITOR_H_

void mmove(WINDOW *wnd, int ny, int nx);
void backspace(WINDOW *wnd);
void open_file(WINDOW *wnd, char *path);
void save(WINDOW *wnd);

#endif

