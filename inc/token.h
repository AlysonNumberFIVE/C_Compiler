
#ifndef TOKEN_H
#define TOKEN_H

#include "compiler.h"

#define AND     256
#define BREAK   258
#define DO      259
#define ELSE    260
#define EQ      261
#define FALSE   262
#define GE      263
#define ID      264
#define IF      265
#define INDEX   266
#define LE      267
#define MINUS   268
#define NE      269
#define NUM     270
#define OR      271`

t_token *new_token(char *name, char *type);
t_token *push_token(t_token *first, char *name, char *type);

#endif
