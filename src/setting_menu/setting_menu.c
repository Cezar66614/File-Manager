#include "setting_menu.h"

void open_setting_win()
{
    clear();
    refresh();

    int y_max, x_max, win_height, win_width, start_y, start_x, setting_key;
    getmaxyx(stdscr, y_max, x_max);
    win_height = y_max - 20;
    win_width = x_max - 20;
    start_y = 10;
    start_x = 10;

    WINDOW *setting_win = newwin(win_height, win_width, start_y, start_x);

    box(setting_win, 0, 0);
    wprintw(setting_win, "Setting Window");
    // refresh();
    wrefresh(setting_win);

    char *choices[] = {"menu1",  "menu2",  "menu3",  "menu4",  "menu5",
                       "menu6",  "menu7",  "menu8",  "menu9",  "menu10",
                       "menu11", "menu12", "menu13", "menu14", "menu15"};
    keypad(setting_win, true);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    attr_t Highlight_1 = A_REVERSE | COLOR_PAIR(1);
    int choice;
    int highlight = 0;

    while (1)
    {
        for (int i = 0; i < 15; i++)
        {
            if (i == highlight)
            {
                wattron(setting_win, Highlight_1);
            }
            mvwprintw(setting_win, i + 2, 10, "%s", choices[i]);

            wattroff(setting_win, Highlight_1);
        }

        choice = wgetch(setting_win);

        switch (choice)
        {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                {
                    highlight = 0;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 15)
                {
                    highlight = 14;
                }
                break;
            default:
                break;
        }
        if (choice == 10)
        {
            break;
        }
    }

    delwin(setting_win);
}
