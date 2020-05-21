
#include "../inc/compiler.h"

t_token *new_token(char *name, char *type)
{
    t_token *new;

    new = (t_token *)malloc(sizeof(t_token));
    new->name = strdup(name);
    new->type = strdup(type);
    new->next = NULL;
    return (new);
}

t_token *add_token(t_token *first, char *name, char *type)
{
    t_token *last;

    last = first;
    while (last->next)
        last = last->next;
    last->next = (t_token *)malloc(sizeof(t_token));
    last->next->name = strdup(name);
    last->next->type = strdup(type);
    last->next->next = NULL;
    return (last);
}

t_token *push_token(t_token *first, char *name, char *type)
{
    t_token *last;

    last = first;
    if (last == NULL)
    {
        last = new_token(name, type);
    }
    else
    {
        last = add_token(first, name, type);
        last = first;
    }
    return (last);
}
