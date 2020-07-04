
#ifndef _PREPROC_
#define _PREPROC_

#include "compiler.h"
#include <stdio.h>
#include <unistd.h>

char        *handle_include(char *content, size_t sizei, char *filename);
t_macro     *push_define(t_macro *head, char *name);
size_t      skip_whitespace(char *buffer, size_t start, size_t length);

#endif
