#include <ncurses.h>

#include "filesInDir.h"

int main(void)
{
    fileViewer_t fV = (fileViewer_t){"."};
    initscr();  // Initialise la structure WINDOW et autres paramètres
    printw("Hello World");  // Écrit Hello World à l'endroit où le curseur lo
                            // ique es positionné
    refresh();  // Rafraîchit la fenêtre courante afin de voir le message a
                // paraître
    displayFilesOfDir(fV);
    getch();   // On attend que l'utilisateur appui sur une touche pour quitter
    endwin();  // Restaure les paramètres par défaut du terminal
    return 0;
}
