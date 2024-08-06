#include <ncurses.h>
#include <string.h>

#include "dsa/node.h"
#include "dsa/stack.h"
#include "filesInDir.h"
#include "setting_menu/setting_menu.h"

int main(void)
{
    fileViewer_t fV = (fileViewer_t){};
    fV.path = malloc(strlen("./"));
    strcpy(fV.path, "./");
    stack_init(&fV.pathWalker);
    node_t *pth = malloc(sizeof(node_t));
    node_init(pth);
    pth->data = malloc(strlen("./"));
    strcpy(pth->data, "./");
    stack_push(&fV.pathWalker, pth);

    initscr();  // Initialise la structure WINDOW et autres paramètres
    printw("Hello World");  // Écrit Hello World à l'endroit où le curseur lo
                            // ique es positionné
    refresh();  // Rafraîchit la fenêtre courante afin de voir le message a
                // paraître
    displayFilesOfDir(&fV);
    // getch();   // On attend que l'utilisateur appui sur une touche pour
    // quitter
    endwin();  // Restaure les paramètres par défaut du terminal
    return 0;
}
