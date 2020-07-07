

#include "../inc/compiler.h"


t_stack *new_stack(char *function_name)
{
    t_stack *new;

    new = (t_stack *)malloc(sizeof(t_stack));
    new->funct_name = strdup(function_name);
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

t_stack *add_stack(t_stack *head, char *function_name)
{
    t_stack *top;

    top = head;
    while (top->next)
        top = top->next;
    top->next = new_stack(function_name);
    top->next->prev = top;
    return (top);
}

t_stack *push_stack(t_stack *head, char *function_name)
{
    t_stack *top;

    top = head;
    if (top == NULL)
        top = new_stack(function_name);
    else
    {
        top = add_stack(top, function_name);
        top = head;
    }
    return (head);
}

t_stack *pop_stack(t_stack *top)
{
    t_stack *to_free;

    to_free = top;
    top = top->prev;
    free(to_free->funct_name);
    free(to_free);
}




