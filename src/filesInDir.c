#include "filesInDir.h"

#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// LINK:
// https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
//  This is cross platform file reading
#include "dsa/node.h"
#include "packages/tinydir/tinydir.h"

void __redraw(fileViewer_t *fV, WINDOW *dir_win)
{
    clear();    // empty the screen
    refresh();  // show the empty screen

    // draws a nice border around the window
    wattron(dir_win, BD_FLAGS);
    box(dir_win, 0, 0);
    wattroff(dir_win, BD_FLAGS);

    mvwprintw(dir_win, 0, 0, "current directory is: %s", fV->path);
}

void __rebuild_path(fileViewer_t *fV)
{
    // runs the queue twice. one gets the total length of the queue
    // the other populates the fileViewer path with the accurate path
    uint16_t length = 0;
    for (fV->pathWalker.current = &fV->pathWalker.head; fV->pathWalker.current;
         fV->pathWalker.current = fV->pathWalker.current->child)
    {
        length += strlen(fV->pathWalker.current->data);
    }
    free(fV->path);
    fV->path = malloc(sizeof(char) * length + 1);
    memset(fV->path, 0, length + 1);

    for (fV->pathWalker.current = &fV->pathWalker.head; fV->pathWalker.current;
         fV->pathWalker.current = fV->pathWalker.current->child)
    {
        fV->path = strcat(fV->path, fV->pathWalker.current->data);
    }
}

void displayFilesOfDir(fileViewer_t *fV)
{
    // limits so it only displays the next _ files
    static const ulong MAX_FILE_DISP = 10;

    uint32_t input;  // char that was input
    // ftd is the file index. this is drawn on the top of the screen
    // > the next MAX_FILE_DISP files are drawn
    // si is the seleted index displayed so it wont only highlight the top file
    // > this is basically responsible for the scrolling
    uint8_t file_to_disp = 0, sel_index = 0;
    uint16_t y_max, x_max, h_win, w_win, y_start, x_start;
    tinydir_dir dir;
    tinydir_file file;
    WINDOW *dir_win = NULL;

    // Initialises the window i guess
    getmaxyx(stdscr, y_max, x_max);
    h_win = y_max - 20;
    w_win = x_max - 20;
    y_start = 10;
    x_start = 10;
    dir_win = newwin(h_win, w_win, y_start, x_start);
    // LINK:
    // https://stackoverflow.com/questions/18837836/how-can-i-hide-the-cursor-in-ncurses
    curs_set(0);
    noecho();

    // Now it will only display n files at once, where n is MAX_FILE_DISP
    do
    {
        __redraw(fV, dir_win);
        tinydir_open_sorted(&dir, fV->path);
        // this draws from file_to_disp to file_to_disp + MAX_FILE_DISP
        for (uint8_t file_index = file_to_disp;
             file_index < (file_to_disp + MAX_FILE_DISP) &&
             (file_index < dir.n_files);
             ++file_index)
        {
            tinydir_readfile_n(&dir, &file, file_index);

            // this then highlights the selected index of the file
            // selected index is offset to 0 -> MAX_FILE_DISP so to make it
            //   accurate we add file_to_disp
            wattron(dir_win,
                    SEL_FILE_FLAG * (file_index == (file_to_disp + sel_index)));
            mvwprintw(dir_win, file_index + 2 - file_to_disp, 10, "%s%s%s",
                      file.name, file.is_dir ? "/" : "", "                   ");
            wattroff(dir_win, SEL_FILE_FLAG);
        }

        input = wgetch(dir_win);
        switch (input)
        {
            case 'k':
                // Only decrease the file index if the selected index is at the
                //   top of the file (the user wants to go back)
                file_to_disp -= sel_index == 0 && file_to_disp > 0;
                // always ensure it is between 0 and MAX_FILE_DISP - 1
                sel_index -= (sel_index < MAX_FILE_DISP) && (sel_index > 0);
                break;
            case 'j':
                // only draw the files up until dir.n_files - MAX_FILE_DISP
                // this is because the next MAX_FILE_DISP files are drawn
                // so we stop before so all files are shown
                file_to_disp += file_to_disp < (dir.n_files - MAX_FILE_DISP);
                // if file_to_disp is at the end of the files, we need to
                //   increment the selected index (the scrolling effect)
                // because we dont want to highlight unless the file_to_disp is
                //   at the end of the files, we use the AND statement
                sel_index += file_to_disp >= (dir.n_files - MAX_FILE_DISP) &&
                             (sel_index < MAX_FILE_DISP - 1);
                break;
            case '\n':
                tinydir_readfile_n(&dir, &file, file_to_disp + sel_index);
                if (file.is_dir)
                {
                    // if the file is a directory, we need to change the path
                    //   to the new directory
                    if (strcmp(file.name, ".") == 0)
                    {
                    }
                    else
                    {
                        // go to the parent directory
                        if ((strcmp(file.name, "..") == 0) &&
                            (fV->pathWalker.tail != &fV->pathWalker.head) &&
                            !(strcmp(fV->pathWalker.tail->data, "../") == 0))
                        // the last check ensures you can go back twice
                        // because without the last check it would go to the
                        // parent diretory instead of exiting the current one
                        {
                            fV->pathWalker.current = stack_pop(&fV->pathWalker);
                            free(fV->pathWalker.current->data);
                            free(fV->pathWalker.current);
                            fV->pathWalker.tail->child = NULL;
                        }
                        else
                        {
                            // go to the subdirectory
                            node_t *subdir = malloc(sizeof(node_t));
                            node_init(subdir);
                            subdir->data =
                                malloc(sizeof(char) * strlen(file.name) + 2);
                            strcpy(subdir->data, file.name);
                            ((char *)subdir->data)[strlen(file.name)] =
                                PATH_SEP;
                            ((char *)subdir->data)[strlen(file.name) + 1] =
                                '\0';
                            stack_push(&fV->pathWalker, subdir);
                        }
                        __rebuild_path(fV);
                        file_to_disp = 0;
                        sel_index = 0;
                    }
                }
                break;
        }
        tinydir_close(&dir);
    } while (input != 'q');

    delwin(dir_win);
}
