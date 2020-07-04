

#ifndef SYMBOL_H
#define SYMBOL_H

#include "compiler.h"

void        print_variable(t_variable *vars);
t_variable  *push_variable(t_variable *head, char *name,
            char *datatype, char *content);
t_scope     *push_scope(t_scope *head, t_variable *vars);
t_scope     *pop_scope(t_scope *head);


#endif
