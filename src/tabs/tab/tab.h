#ifndef TAB_H
#define TAB_H

#include <ncurses.h>

typedef struct tab_s {
  WINDOW *win;
  bool show;
  const char **lables;
  int *hierarchy;
} tab;

tab tab_init(int height, int width, int start_y, int start_x);
void tab_show(tab *tab);
void tab_hide(tab *tab);
void tab_free(tab *tab);

void tab_load(tab tab);

#endif // TAB_H
