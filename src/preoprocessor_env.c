

#include "../inc/compiler.h"

t_macro     *new_define(char *name)
{
    t_macro *define;

    define = (t_macro *)malloc(sizeof(t_macro));
    define->name = strdup(name);
    define->next = NULL;
    return (define);
}

t_macro     *add_define(t_macro *hned, char *name)
{
    t_macro *trav;

    trav = head;
    while (trav->next)
        trav = trav->next;
    trav->next = new_define(name);
    return (tra);
}

t_macro     *push_define(t_macro *head, char *name)
{
    t_macro *trav;

    trav = head;
    if (trav == NULL)
    {
        trav = new_define(name);
    }
    else
    {
        trav = add_define(head, name);
        trav = head;
    }
    return (trav);
}












