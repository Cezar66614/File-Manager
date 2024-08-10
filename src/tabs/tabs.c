#include "tabs.h"
#include "tab/tab.h"

static tab tabs[MAX_TABS];

void tabs_init(void) {
  int i;
  for (i = 0; i < MAX_TABS; ++i) {
    tabs[i] = tab_init(10, 10, 1, 10 * i);
    // wprintw(tabs[i].win, "Y");
  }
}
void tabs_show(void) {
  int i;
  for (i = 0; i < MAX_TABS; ++i) {
    if (tabs[i].show == true) tab_show(&tabs[i]);
  }
}
void tabs_hide(void) {
  int i;
  for (i = 0; i < MAX_TABS; ++i) tabs[i].show = false;
  refresh();
}
void tabs_free(void) {
  int i;
  for (i = 0; i < MAX_TABS; ++i) tab_free(&tabs[i]);
}
