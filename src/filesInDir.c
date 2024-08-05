#include "filesInDir.h"

#include <ncurses.h>
#include <stdint.h>

// https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
// This is cross platform file reading
#include "packages/tinydir/tinydir.h"

void displayFilesOfDir(fileViewer_t fV)
{
    // limits so it only displays the next _ files
    static const ulong MAX_FILE_DISP = 10;

    uint32_t input;
    uint8_t sel_index = 0;
    uint16_t y_max, x_max, h_win, w_win, y_start, x_start;
    tinydir_dir dir;
    WINDOW *dir_win = NULL;

    clear();    // empty the screen
    refresh();  // show the empty screen

    // Initialises the window i guess
    getmaxyx(stdscr, y_max, x_max);
    h_win = y_max - 20;
    w_win = x_max - 20;
    y_start = 10;
    x_start = 10;
    dir_win = newwin(h_win, w_win, y_start, x_start);

    // draws a nice border around the window
    wattron(dir_win, BD_FLAGS);
    box(dir_win, 0, 0);
    wattroff(dir_win, BD_FLAGS);
    curs_set(0);

    wprintw(dir_win, "current directory is: %s", fV.path);

    tinydir_open_sorted(&dir, fV.path);

    // Now it will only display n files at once, where n is MAX_FILE_DISP
    do
    {
        for (uint8_t file_index = sel_index; file_index < (dir.n_files);
             ++file_index)
        {
            tinydir_file file;
            tinydir_readfile_n(&dir, &file, file_index);

            wattron(dir_win, SEL_FILE_FLAG * (file_index == sel_index));
            mvwprintw(dir_win, file_index + 2, 10, "%s%s", file.name,
                      file.is_dir ? "/" : "");
            wattroff(dir_win, SEL_FILE_FLAG);
        }
        input = wgetch(dir_win);
        switch (input)
        {
            case 'k':
                sel_index -= (sel_index > 0);
                break;
            case 'j':
                sel_index += sel_index < (dir.n_files);
                break;
        }
        wrefresh(dir_win);
    } while (input != 'q');

    tinydir_close(&dir);
    delwin(dir_win);
}
