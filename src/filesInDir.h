#pragma once

#include "dsa/stack.h"

#define BD_FLAGS A_REVERSE
#define SEL_FILE_FLAG A_REVERSE

// TODO: Change this for windows mac or linux
// Maybe use a macro or make it part of the build system
#define PATH_SEP '/'

void get_visible_files(stack_t *stk, char *path, uint8_t maxFiles,
                       uint8_t offset);
char *build_path(char *storage, stack_t *stk);
void file_push(stack_t *stk, char *file);
void dir_push(stack_t *stk, char *subdir);
void dir_pop(stack_t *stk);
