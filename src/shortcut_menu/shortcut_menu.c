#include "shortcut_menu.h"

#define PLACEHOLDER_HEADER "<shortcut>"


int main(void)
{
    // initialize stdscr
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

    // create shortcut menu
    initializeShortcutMenu();

    // end program
    endwin();
    return 0;
}