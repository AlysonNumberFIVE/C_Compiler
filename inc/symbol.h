

#ifndef SYMBOL_H
#define SYMBOL_H

#include "compiler.h"

t_symbol    *delete_from_index(t_symbol *first, int index);
t_symbol    *merge_inherited_symbols(t_symbol *first, t_symbol *second);
t_scope     *push_scope(t_scope *head, t_symbol *symbols);
t_scope     *pop_scope(t_scope *head);
void        clear_all_variables(t_symbol *first);
t_symbol    *push_variable(t_symbol *first, char *name,
                char *datatype, short size,
                char *key, char *value,
                short mem_type,
                size_t array_size,
                uint32_t decl_line,
                uint32_t usage_line);
t_var       *push_var(t_var *var, char *variable, char *cont);
void        print_vars(t_var *list);

t_var       *pusH_var(t_var *var, char *variable, char *cont);
bool        reset_variable(t_symbol *symbol_list, char *variable_name,
    char *new_value);
t_symbol    *lookup_variable(t_symbol *symbol_list, char *variable_name);

#endif
