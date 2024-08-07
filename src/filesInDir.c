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

char *build_path(char *storage, stack_t *stk) {
    // runs the queue twice. one gets the total length of the queue
    // the other populates the fileViewer path with the accurate path
    uint16_t length = 0;
    for (stk->current = &stk->head; stk->current;
         stk->current = stk->current->child) {
        length += strlen(stk->current->data);
    }
    free(storage);
    storage = malloc(sizeof(char) * length + 1);
    memset(storage, 0, length + 1);

    for (stk->current = &stk->head; stk->current;
         stk->current = stk->current->child) {
        storage = strcat(storage, stk->current->data);
    }
    return storage;
}

void get_visible_files(stack_t *stk, char *path, uint8_t maxFiles,
                       uint8_t offset) {
    tinydir_dir dir;
    tinydir_file file;

    tinydir_open_sorted(&dir, path);

    if ((offset + maxFiles) > dir.n_files) {
        printf("too many files in directory: %s\n", path);
        printf("will only show %ld files\n", dir.n_files - offset);
        maxFiles = dir.n_files - offset;
    }
    for (uint8_t file_index = offset; file_index < (offset + maxFiles);
         ++file_index) {
        tinydir_readfile_n(&dir, &file, file_index);
        file_push(stk, file.name);
    }
}

void file_push(stack_t *stk, char *file) {
    node_t *node = malloc(sizeof(node_t));
    node_init(node, file, strlen(file));
    stack_push(stk, node);
}

void dir_push(stack_t *stk, char *subdir) {
    node_t *node = malloc(sizeof(node_t));
    node_init(node, subdir, strlen(subdir) + 1);
    ((char *)node->data)[strlen(subdir)] = PATH_SEP;
    stack_push(stk, node);
}

void dir_pop(stack_t *stk) {
    // go to the parent directory
    // the last check ensures you can go back twice
    // because without the last check it would go to the
    // parent diretory instead of exiting the current one
    if ((stk->tail != &stk->head) && !(strcmp(stk->tail->data, "../") == 0)) {
        stk->current = stack_pop(stk);
        free(stk->current->data);
        free(stk->current);
        stk->tail->child = NULL;
    } else {
        // go to the subdirectory
        dir_push(stk, "..");
    }
}
