

#include "../inc/compiler.h"

t_symbol    *delete_from_index(t_symbol *first, int index)
{
    int         i;
    t_symbol    *trav;
    t_symbol    *delete;
    t_symbol    *temp;

    i = 0;
    trav = first;
    while (trav)
    {
        if (i == index)
            break;
        trav = trav->next;
        i++;
    }
    delete = trav;
    trav->next = NULL;
    while (delete)
    {
        temp = delete;
        delete = delete->next;
        free(temp);
        temp = NULL;
    }
    return (first);
}

t_symbol    *merge_inherited_symbols(t_symbol *first, t_symbol *second)
{
    t_symbol *head;
    t_symbol *trav;

    head = first;
    trav = first;
    while (trav->next)
        trav = trav->next;
    trav->next = second;
    return (first);
}

