#include "tab.h"

tab tab_init(int height, int width, int start_y, int start_x) {
  tab new_tab;
  new_tab.win = newwin(height, width, start_y, start_x);
  new_tab.show = true;
  return new_tab;
}
void tab_show(tab *tab) {
  if ((*tab).win != NULL) {
    tab->show = true;

    wborder((*tab).win, '|', '|', '-', '-', '+', '+', '+', '+');

    wrefresh((*tab).win);
  }
}
void tab_hide(tab *tab) {
  tab->show = false;
  refresh(); // TODO: draw the rest of the tabs (in the tabs.c)
}
void tab_free(tab *tab) {
  if ((*tab).win != NULL) delwin((*tab).win);
  tab->win = NULL;
  tab->show = false;
}
