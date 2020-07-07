


#include "../inc/symbol.h"

/* 
 typedef struct  s_scope
{
    struct s_symbol *symbols;
    struct s_scope *next;
}   t_scope;
*/  

t_scope     *new_scope(t_variable *variables)
{
    t_scope *new_scope;

    new_scope = (t_scope *)malloc(sizeof(t_scope));
    new_scope->next = NULL;
    new_scope->prev = NULL;
    new_scope->depth = 0;
    new_scope->variables = variables;
    return (new_scope);
}

t_scope     *add_scope(t_scope *head, t_variable variables)
{
    t_scope     *trav;
    int         depth_counter;

    depth_counter = 0;
    trav = head;
    while (trav->next)
    {
        trav = trav->next;
        depth_counter++;
    }
    depth_counter++;
    trav->next = new_scope(variables);
    trav->next->prev = trav;
    return (trav);
}

t_scope     *push_scope(t_scope *head, t_variable *variables)
{
    t_scope *trav;

    trav = head;
    if (trav == NULL)
    {
        head = new_scope(variables);
        trav = head;
    }
    else 
    {
        trav = add_scope(head, variables);
        trav = head;
    }
    return (head);
}

t_scope *pop_scope(t_scope *top)
{
    t_variable  *variables;
    t_variable  *tmp;

    tmp = to_remove->variables;
    while (tmp)
    {
        variables = tmp;
        tmp = tmp->next; 
        free(variables->name);
        if (variables->value)
            free(variables->value);
        free(variables->datatype);
        free(variables);
    }
    top = top->prev;
    free(top);
}

