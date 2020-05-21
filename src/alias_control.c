

#include "../inc/compiler.h"


t_alias     *new_alias(char *name, char *value, int kind)
{
    t_alias *alias;
    
    alias = (t_alias *)malloc(sizeof(t_alias));
    alias->name = strdup(name);
    alias->value = strdup(value);
    if (kind == TYPEDEF)
    {
        alias->is_define = false;
        alias->is_typedef = true;
    }
    else
    {
        alias->is_define = true;
        alias->is_typedef = false;
    }
    alias->next = NULL;
    return (alias);
}

t_alias     *add_alias(t_alias *alias, char *name, char *value,
        int kind)
{
    t_alias     *trav;

    while (trav->next)
        trav = trav->next;
    trav->next = (t_alias *)malloc(sizeof(t_alias));
    trav->next->name = strdup(name);
    trav->next->value = strdup(value);
    if (kind == TYPEDEF)
    {
        trav->next->is_define = false;
        trav->next->is_typedef = true;
    }
    else
    {
        trav->next->is_define = true;
        trav->next->is_typedef = false;
    }
    trav->next->next = NULL;
    return (trav);
}

t_alias     *push_alias(t_alias *alias, char *name, char *value,
    int kind)
{
    t_alias *top;

    top = alias;
    if (top == NULL)
    {
        alias = new_alias(name, value, kind);
    }
    else
    {
        top = add_alias(alias, name, value, kind);
        top = alias;
    }
    return (alias);
}

