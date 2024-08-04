#include "shortcut_menu.h"

// initializes command window
WINDOW* initializeShortcutMenu(void)
{
    int startx, starty, width, height;
    WINDOW* shortcutWindow;

    height = LINES - 3; width = COLS - 3;
    starty = (LINES - height) / 2; startx = (COLS - width) / 2; // calculates a centered placement of the window

    shortcutWindow = newwin(height, width, starty, startx); // create new window and give it a standard border
    box(shortcutWindow, 0, 0);
    wrefresh(shortcutWindow);

    return shortcutWindow;
}

int showShortcutMenu(WINDOW* window)
{

    return SUCCESS;
}

int hideShortcutMenu(WINDOW* window)
{

    return SUCCESS;
}

// function to destroy window
int freeShortcutMenu(WINDOW* window)
{
    box(window, ' ', ' ');
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    delwin(window);
    
    return SUCCESS;
}