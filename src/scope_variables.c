

#include "../inc/compiler.h"

/*
typedef struct  s_symbols
{
    char    *name;
    char    *datatype;
    short   size;
    char    *value;
    uint32_t decl_line;
    uint32_t usage_line;
    struct s_symbols *next;
}   t_symbol;
*/

t_symbol    *new_symbol(char *name, char *datatype,
                        short size, char *value,
                        uint32_t decl_line, uint32_t usage_line)
{
    t_symbol    *first;

    first = (t_symbol *)malloc(sizeof(t_symbol));
    first->name = strdup(name);
    first->datatype = strdup(datatype);
    first->size = size;
    if (value)
        first->value = strdup(value);
    first->decl_line = decl_line;
    first->usage_line = usage_line;
    first->next = NULL;
    return (first);
}

t_symbol    *add_symbol(t_symbol *first, char *name,
                        char *datatype, short size,
                        char *value, uint32_t decl_line,
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
    if (value)
        last->next->value = strdup(value);
    last->next->decl_line = decl_line;
    last->next->usage_line = usage_line;
    last->next->next = NULL;
    return (last);
}

t_symbol    *push_variable(t_symbol *first, char *name,
                char *datatype, short size,
                char *value, uint32_t decl_line,
                uint32_t usage_line)
{
    t_symbol     *last;

    last = first;
    if (last == NULL)
    {
        first = new_symbol(name, datatype, size, value,
            decl_line, usage_line);
    }
    else
    {
        last = add_symbol(first, name, datatype, size,
            value, decl_line, usage_line);
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
    char *value, uint32_t decl_line,
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
        size, value, decl_line, usage_line);
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
            variable->value = strdup(new_value);
            return (true);
        }
        variable = variable->next;
    }
    return (false);
}

