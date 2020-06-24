

#include "../inc/compiler.h"

/*
typedef struct s_datatype
{
    char *name;
    int size;
}   t_datatype;
*/

t_datatype  *new_datatype(char *name, int size)
{
    t_datatype  *new;

    new = (t_datgatyp *)malloc(sizeof(t_datatype));
    new->name = strdup(name);
    new->size = size;
    nkew->next
}
