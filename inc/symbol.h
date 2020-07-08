

#ifndef SYMBOL_H
#define SYMBOL_H

#include "compiler.h"

t_function_table    *push_function(t_function_table *head, char *name,
        char *datatype, bool is_defined, t_variable *variables);
void        print_variable(t_variable *vars);
t_variable    *save_variable(t_token **token, char *stop);
t_variable  *copy_variables(t_variable *list);
t_variable  *push_variable(t_variable *head, char *name,
            char *datatype, char *content);
t_variable  *copy_variables(t_variable *list);
int         merge_variable_list(t_variable *current, t_variable *new);
t_scope     *push_scope(t_scope *head, t_variable *vars);
t_scope     *pop_scope(t_scope *head);


#endif
