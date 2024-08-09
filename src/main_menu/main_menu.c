#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

#define ENTER 10

//We should probably move the input function to main.c
void input(WINDOW *window)
{
    char modes[3][10] = {"Commands", "Write", "Navigate"};
    char currentMode[10] = "Commands";
    int choice;
    int textInput;

    //GOAL : Compare the mode and the currentMode and is the same alternate between writing mode (where everything you type is on the screen) 
    //and Commands mode (where you navigate or invoke a function of shortcut) + could be cool to have a way to move the cursor with like ctrl+w with go from subwin to subwin
   int posY, posX = 1;
    int placeInArray = 0;
    while(1)
    {
        choice = wgetch(window);
        if(choice == ENTER)
        {
            placeInArray += 1;
            if(placeInArray >= 3)
            {
                placeInArray = 0;
            }
            strcpy(currentMode, modes[placeInArray]);
            printw("%s : mode \n", currentMode);
            refresh();
        }
        if(strcmp(currentMode, "Commands") == 0)
        {
            switch (choice) {
                case KEY_UP:
                    printw("You are in commands mode \n");
                    refresh();
                    break;
                case 'q':
                    endwin();
                    break;
            }
        }
        if(strcmp(currentMode, "Write") == 0)
        {
            switch (choice) {
                case 'n':
                    posY++;
                    posX++;
                    move(posY, posX);
                    //go down one LINE
                    break;
                case 'p':
                    posY++;
                    posX++;
                    move(posY, posX);
                    //go up one LINE
                    break;
                default:
                    break;
            }
        }
        if(strcmp(currentMode, "Navigate") == 0)
        {
            switch (choice) 
            {
                case KEY_DOWN:
                    printw("\n");
                    move(10, 20);
                    refresh();
                    break;
                default:
                    break;
            }
        }
        move(LINES+10, COLS+10);
    }
}
int main(void)
{
    initscr();
    clear();
    //noecho();
    //cbreak();
    keypad(stdscr, true);

    WINDOW *path1, *path2, *folder1, *folder2, *hints, *info;

    int highlight = 1;
    int choice = 0;


    int height, width, start_y, start_x;
    height = LINES/8;
    width = COLS/1.1;
    start_y = 0;
    start_x = 5;

    path1 = newwin(height, width, start_y, start_x);
    keypad(path1, true);
    box(path1, 0, 0);
    refresh();
    input(path1);
    endwin();
}
