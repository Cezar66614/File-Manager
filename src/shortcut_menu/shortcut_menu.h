#pragma once

#include <ncurses.h> // library for making windows

// define return values
#ifndef SUCCESS
    #define SUCCESS 0;
#endif
#ifndef FAIL
    #define FAIL -1;
#endif

// initialize prototypes
int initializeShortcutMenu(void);
int showShortcutMenu(void);
int hideShortcutMenu(void);
int freeShortcutMenu(WINDOW* window);


// initializes command window
int initializeShortcutMenu(void)
{
    int startx, starty, width, height;
    int charBuffer;
    WINDOW* shortcutWindow;

    height = 12; width = 24;
    starty = (LINES - height) / 2; startx = (COLS - width) / 2; // calculates a centered placement of the window

    shortcutWindow = newwin(height, width, starty, startx); // create new window and give it a standard border
    box(shortcutWindow, 0, 0);
    wrefresh(shortcutWindow);

    // free menu and close program after keypress
    wgetch(shortcutWindow);
    freeShortcutMenu(shortcutWindow);
    return SUCCESS;
}

int showShortcutMenu(void)
{

    return SUCCESS;
}

int hideShortcutMenu(void)
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