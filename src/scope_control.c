


#include "../inc/symbol.h"

/* 
 typedef struct  s_scope
{
    struct s_symbol *symbols;
    struct s_scope *next;
}   t_scope;
*/  

t_scope     *new_scope(t_symbol *inherited_symbols)
{
    t_scope *new_scope;

    new_scope = (t_scope *)malloc(sizeof(t_scope));
    new_scope->inherited_symbols = inherited_symbols;
    new_scope->symbols = NULL;
    new_scope->next = NULL;
    new_scope->depth = 0;
    return (new_scope);
}

t_scope     *add_scope(t_scope *head, t_symbol *inherited_symbols)
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
    trav->next = (t_scope *)malloc(sizeof(t_scope));
    trav->next->inherited_symbols = inherited_symbols;
    trav->next->symbols = NULL;
    trav->next->depth = depth_counter;
    trav->next->next = NULL;
    return (trav);
}

t_scope     *push_scope(t_scope *head, t_symbol *inherited_symbols)
{
    t_scope *trav;

    trav = head;
    if (trav == NULL)
    {
        head = new_scope(inherited_symbols);
        trav = head;
    }
    else 
    {
        trav = add_scope(head, inherited_symbols);
        trav = head;
    }
    return (trav);
}

t_scope    *pop_scope(t_scope *head)
{
    t_scope *trav;
    t_scope *temp;

    trav = head;
    while (trav->next->next)
        trav = trav->next;
    
    temp = trav->next;
    free(temp);
    trav->next = NULL;
    return (head);
}


