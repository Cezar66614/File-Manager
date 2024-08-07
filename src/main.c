#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "dsa/node.h"
#include "dsa/stack.h"
#include "filesInDir.h"

int main(void) {
    /* node_t *pth = malloc(sizeof(node_t));
    node_init(pth);
    pth->data = malloc(strlen("./"));
    strcpy(pth->data, "./");
    stack_push(&dirWalker, pth); */
    remove("./file");
    mkdir("./deez", 0);

    /* initscr();  // Initialise la structure WINDOW et autres paramètres
    printw("Hello World");  // Écrit Hello World à l'endroit où le curseur lo
                            // ique es positionné
    refresh();  // Rafraîchit la fenêtre courante afin de voir le message a
                // paraître
    // getch();   // On attend que l'utilisateur appui sur une touche pour
    // quitter
    endwin();  // Restaure les paramètres par défaut du terminal */
    return 0;
}
