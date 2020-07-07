

#include "../inc/symbol.h"
#include "../inc/compiler.h"

void        print_variable(t_variable *vars)
{
    t_variable  *trav;

    trav = vars;
    while (trav)
    {
        printf("trav-> name :%s\n", trav->name);
        printf("trav->datatype: %s\n", trav->datatype);
        if (trav->value)
            printf("trav->content : %s\n", trav->value);
        else
            printf("NULL\n");
        trav = trav->next;
    }
}

t_variable  *new_variable(char *name, char *datatype, char *content)
{
    t_variable  *new;

    new = (t_variable *)malloc(sizeof(t_variable));
    new->name = strdup(name);
    new->datatype = strdup(datatype);
    new->value = strdup(content);
    new->next = NULL;
    return (new);
}

t_variable  *add_variable(t_variable *head, char *name,
        char *datatype, char *content)
{
    t_variable  *trav;

    trav = head;
    while (trav->next)
        trav = trav->next;
    trav->next = new_variable(name, datatype, content);
    return (trav);
}

t_variable  *push_variable(t_variable *head, char *name, 
            char *datatype, char *content)
{
    t_variable  *trav;

    trav = head;
    if (trav == NULL)
    {
        printf("eight\n");
        trav = new_variable(name, datatype, content); 
    }
    else
    {
        trav = add_variable(head, name, datatype, content);
        trav = head;
    }
    return (trav);
}

int     merge_variable_list(t_variable *current, t_variable *new)
{
    int index;
    t_variable *list;

    index = 0;
    while (list)
    {
        list = list->next;
        index++;
    }
    list = new;
    return (index);
}

