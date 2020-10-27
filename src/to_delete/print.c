
/*
#include "../inc/compiler.h"
*/

void    print_variables(t_variable *variables)
{
    t_variable  *trav;

    trav = variables;
    while (trav)
    {
        printf("NEW VARIABLES ====================\n");
        printf("name : %s\n", trav->name);
        printf("datatype : %s\n", trav->datatype);
        printf("value : %s\n", trav->value);
        printf("==================================\n\n");
        trav = trav->next;
    }
}

void    print_function(t_function_table *functions)
{
    t_function_table *trav;

    trav = functions;
    while (trav)
    {
        printf("function_name : %s\n", trav->function_name);
        printf("datatype : %s\n", trav->datatype);
        printf("(");
        if (trav->variables) {
            print_variables(trav->variables);
	}
        else
            printf("void\n");
        printf(")");
        trav = trav->next;
    }
}

void    print_scope(t_scope *scope)
{
    t_scope *trav;

    trav = scope;
    while (trav)
    {
        printf("Depth %d\n", trav->depth);
        if (trav->variables)
            print_variables(trav->variables);
        else
            printf("NO VARIABLES\n");
        trav = trav->next;
    }
}
