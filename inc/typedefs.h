#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "compiler.h"
#include "token.h"

typedef struct  s_typedef_list
{
        char *name;
        t_token *replace;
        struct s_typedef_list *next;
}       t_typedef;


t_token	*resolve_typedefs(t_token *name);

#endif
