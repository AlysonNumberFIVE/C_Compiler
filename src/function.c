

#include "../inc/compiler.h"

t_function_table    *new_function(char *name, char *datatype,
        bool is_defined, t_variable *variables)
{
    t_function_table    *new;

    new = (t_function_table *)malloc(sizeof(t_function_table));
    new->function_name = strdup(name);
    new->datatype = strdup(datatype);
    new->variables = variables;
    new->is_defined = is_defined;
    new->next = NULL;
    return (new);
}

t_function_table    *add_function(t_function_table *head, char *name,
    char *datatype, bool is_defined, t_variable *variables)
{
    t_function_table    *trav;

    trav = head;
    while (trav->next)
        trav = trav->next;
    trav->next = new_function(name, datatype, is_defined, variables);
    return (trav);
}

t_function_table    *push_function(t_function_table *head, char *name,
        char *datatype, bool is_defined, t_variable *variables)
{
    t_function_table    *trav;

    trav = head;
    if (trav == NULL)
        trav = new_function(name, datatype, is_defined, variables);
    else
    {
        trav = add_function(head, name, datatype, is_defined,
            variables);
        trav = head;
    }
    return (trav);
}

