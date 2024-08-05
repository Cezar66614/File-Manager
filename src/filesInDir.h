#pragma once

typedef struct fileViewer
{
    char *path;
} fileViewer_t;

void displayFilesOfDir(fileViewer_t fV);
