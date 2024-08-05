#pragma once

#define BD_FLAGS A_REVERSE
#define SEL_FILE_FLAG A_REVERSE

typedef struct fileViewer
{
    char *path;
} fileViewer_t;

void displayFilesOfDir(fileViewer_t fV);
