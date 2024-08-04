#pragma once

#include <ncurses.h> // library for making windows

// define return values
#ifndef SUCCESS
    #define SUCCESS 0;
#endif
#ifndef FAIL
    #define FAIL -1;
#endif
// placeholder for shortcut names
#define PLACEHOLDER_HEADER "<shortcut>"

// initialize prototypes
WINDOW* initializeShortcutMenu(void); // creates a new window as a container for the shortcut menu, returns the address of the window
int showShortcutMenu(WINDOW* window);
int hideShortcutMenu(WINDOW* window);
int freeShortcutMenu(WINDOW* window);