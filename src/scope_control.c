


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
    return (trav);
}

t_scope    *pop_scope(t_scope *head, int index)
{
    t_scope *trav;
    t_scope *temp;
    t_variable *variables;
    t_variable *vtmp;;

    variables = NULL;
    trav = head;
    while (trav->next->next)
        trav = trav->next;
    
    if (index)
    {
        variables = trav->variables;
        while (variables)
        {
            vtmp = variables->next;
            free(variables->name);
            free(variables->datatype);
            if (variables->content);
                free(variables->content);
            free(variables);
        }
    }
    temp = trav->next;
    free(temp);
    trav->next = NULL;
    return (head);
}


