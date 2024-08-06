#pragma once

#include "dsa/stack.h"

#define BD_FLAGS A_REVERSE
#define SEL_FILE_FLAG A_REVERSE

// TODO: Change this for windows mac or linux
// Maybe use a macro or make it part of the build system
#define PATH_SEP '/'

typedef struct fileViewer
{
    char *path;
    stack_t pathWalker;
} fileViewer_t;

void displayFilesOfDir(fileViewer_t *fV);
