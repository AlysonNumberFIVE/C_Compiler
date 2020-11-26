

#ifndef TAC_H
#define TAC_H

#include "compiler.h"

typedef struct  s_tree
{
        char *type;
        t_token *tokens;
        struct s_tree *next;
}       t_tree;

t_tree	*push_tree(t_tree *head, char *type, t_token *tokens);


#endif
