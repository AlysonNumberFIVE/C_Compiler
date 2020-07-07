

#include "../inc/semantic.h"

char    *datatype_name(char *name, char *to_add)
{
    char    *string;

    string = join(name, to_add);
    free(name);
    name = join(string, " ");
    free(string);
    return (name);
}

bool    assert_second_order(char *to_check)
{
    extern char primitives[33][9];
    int i;

    for (i = 0; i < 12; i++)
    {
        if (strcmp(primitives[i], to_check) == 0)
            return (true);
    }
    return (false);
}

bool    assert_first_order(char *to_check)
{
    extern char first_order[4][9];
    int i;

    for (i = 0; i < 3; i++)
    {
        if (strcmp(first_order[i], to_check) == 0)
            return (true);
    }
    return (false);
}

int     determine_pointer_depth(t_token *list)
{
    int depth;

    depth = 0;
    while (strcmp(list->name, "*") == 0 && list)
    {
        list = list->next;
        depth++;
    }
    return (depth);
}
