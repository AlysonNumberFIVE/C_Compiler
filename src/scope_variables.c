
#include <stdlib.h>
#include "../inc/compiler.h"

/*
typedef struct  s_variable
{
    char        *var;
    char        *content;
    struct s_variable   *next;
}   t_var;
   
   
typedef struct  s_symbols
{
    char                *name;
    char                *datatype;
    short               size;
    struct s_symbols    **array;
    size_t              array_size;
    uint32_t            decl_line;
    uint32_t            usage_line;
    t_hashtable         *value;
    struct s_symbols    *next;
}   t_symbol;
*/


t_var   *new_var(char *variable, char *cont)
{
    t_var   *new;

    new = (t_var *)malloc(sizeof(t_var));
    new->var = strdup(variable);
    new->content = strdup(cont);
    new->next = NULL;
    return (new);
}

t_var   *add_var(t_var *var,char *variable, char *cont)
{
    t_var   *trav;

    trav = var;
    while (var->next)
        trav = trav->next;
    trav->next = new_var(variable, cont);
    return (trav);
}

t_var   *push_var(t_var *var, char *variable, char *cont)
{
    t_var   *last;

    last = var;
    if (last == NULL)
    {
        var = new_var(variable, cont);
    }
    else
    {
        last = add_var(var, variable, cont);
        last = var;
    }
    return (var);
}

void    print_vars(t_var *list)
{
    t_var   *trav;
 
    trav = list;
    while (trav)
    {
        printf("%s\n", trav->var);
        printf("%s\n\n", trav->content);
        trav = trav->next;
    }
}

static t_symbol    **handle_variable_array(size_t array_size)
{
    t_symbol    **symbol_array;
    
    symbol_array = (t_symbol **)malloc(sizeof(t_symbol *));
    return (symbol_array);
}


t_symbol    *new_symbol(char *name, char *datatype, short size, 
                        char *key, char *value,
                        short mem_type,
                        size_t array_size,
                        uint32_t decl_line,
                        uint32_t usage_line)
{
    t_symbol    *first;

    first = (t_symbol *)malloc(sizeof(t_symbol));
    first->name = strdup(name);
    first->datatype = strdup(datatype);
    first->size = size;
    first->mem_type = mem_type;
    first->value = push_var(first->value, key, value);
    if (array_size > 0)
        first->array = handle_variable_array(array_size);
    first->decl_line = decl_line;
    first->usage_line = usage_line;
    first->next = NULL;
    return (first);
}

t_symbol    *add_symbol(t_symbol *first, char *name,
                        char *datatype, short size,
                        char *key, char *value,
                        short mem_type,
                        size_t array_size,
                        uint32_t decl_line,
                        uint32_t usage_line)
{
    t_symbol    *last;

    last = first;
    while (last->next)
        last = last->next;
    last->next = (t_symbol *)malloc(sizeof(t_symbol));
    last->next->name = strdup(name);
    last->next->datatype = strdup(datatype);
    last->next->size = size;
    last->next->mem_type = mem_type;
    last->next->value = push_var(last->next->value, key, value);
    if (array_size > 0)
        last->next->array = handle_variable_array(array_size);
    last->next->decl_line = decl_line;
    last->next->usage_line = usage_line;
    last->next->next = NULL;    
    return (last);
}

t_symbol    *push_variable(t_symbol *first, char *name,
                char *datatype, short size,
                char *key, char *value,
                short mem_type,
                size_t array_size,
                uint32_t decl_line,
                uint32_t usage_line)
{
    t_symbol     *last;

    last = first;
    if (last == NULL)
    {
        first = new_symbol(name, datatype, size, key, value,
             mem_type, array_size, decl_line, usage_line);
    }
    else
    {
        last = add_symbol(first, name, datatype, size,
            key, value, mem_type, array_size, decl_line,
            usage_line);
        last = first;
    }
    return (first);
} 

void        clear_all_variables(t_symbol *first)
{
    t_symbol    *last;

    while (first)
    {
        last = first->next;
        free(first->name);
        free(first->datatype);
        free(first->value);
        free(first);
        first = last;
    }
    first = NULL;
}

t_symbol    *insert_variable(t_symbol *symbol_list, char *name,
    char *datatype, short size,
    char *key, char *value, 
    short mem_type,
    size_t array_size,
    uint32_t decl_line,
    uint32_t usage_line)
{
    t_symbol    *variable;

    variable = symbol_list;    
    while (variable)
    {
        if (strcmp(variable->name, name) == 0)
            return (NULL);
        variable = variable->next;
    }
    symbol_list = push_variable(symbol_list, name, datatype,
        size, key, value, mem_type, array_size, decl_line, usage_line);
    return (symbol_list); 
}

t_symbol    *lookup_variable(t_symbol *symbol_list, char *variable_name)
{
    t_symbol    *variable;

    variable = symbol_list;
    while (variable)
    {
        if (strcmp(variable->name, variable_name) == 0)
            return (variable);
        variable = variable->next;
    }
    return (NULL);
}

bool    reset_variable(t_symbol *symbol_list, char *variable_name,
    char *new_value)
{
    t_symbol    *variable;

    variable = symbol_list;
    while (variable)
    {
        if (strcmp(variable->name, variable_name) == 0)
        {
            free(variable->value);
           // variable->value = strdup(new_value);
            return (true);
        }
        variable = variable->next;
    }
    return (false);
}

