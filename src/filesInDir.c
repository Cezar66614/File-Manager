#include "filesInDir.h"

#include <ncurses.h>
#include <stdio.h>
#include <sys/types.h>

// https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
// This is cross platform file reading
#include "packages/tinydir/tinydir.h"

void displayFilesOfDir(fileViewer_t fV)
{
    // I dont know why i need this but it seems to work in settings menu
    // TODO: Understand how this works but it aint broke so dont fix
    clear();
    refresh();

    // Initialises the window i guess
    uint y_max, x_max, win_height, win_width, start_y, start_x;
    getmaxyx(stdscr, y_max, x_max);
    win_height = y_max - 20;
    win_width = x_max - 20;
    start_y = 10;
    start_x = 10;

    WINDOW *directory = newwin(win_height, win_width, start_y, start_x);
    box(directory, 0, 0);
    wprintw(directory, "current directory is: %s", fV.path);
    wrefresh(directory);

    // This function is called often, so to reduce syscalls I declare them
    // static
    tinydir_dir dir;
    tinydir_open_sorted(&dir, fV.path);
    uint highlight_index = 0;
    keypad(directory, true);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    for (unsigned int i = 0; i < dir.n_files; i++)
    {
        tinydir_file file;
        tinydir_readfile_n(&dir, &file, i);

        if (file.is_dir)
        {
            // printf("/");
        }
        printf("%d\n", mvwprintw(directory, i + 2, 10, "%s", file.name));
    }

    tinydir_close(&dir);
    delwin(directory);
}
