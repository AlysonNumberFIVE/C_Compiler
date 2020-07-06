

#include "../inc/compiler.h"

t_scope             *g_symbol_table = NULL;
t_function_table    *function_talbe = NULL;
#define FUNCTION 1
#define VARIABLE 2

int    skip_stars(t_token *token)
{
    while (token && strcmp(token->name, "*") == 0)
        token = token->next;
    if (token)
        return (1);
    return (0);
}

int     variable_or_function(t_token *tokens)
{
    t_token     *list;

    list = token;
    if (assert_first_order(list->name) == true)
    {
        if (assert_second_order(list->next->name) == true)
            list = list->next->next;
    }
    else if (assert_second_order(list->name) == true)
        list = list->next;
    if (list && strcmp(list->name, "*") == 0)
        skip_stars(list);
    else
        return (-1);
    if (strcmp(list->type, "ID") == 0)
        list = list->next;
    if (strcmp(list->name, "(") == 0)
        return (1);
    if (strcmp(list->name, ";") == 0 || strcmp(list->name, "=") == 0)
        return (2);
    return (-1);
}

void    create_variable(t_token *token)
{
    t_variable  *variable;
    t_scope     *local_sym;
    t_variable  *local_var;

    variable = save_variable(token, ";");
    local_sym = g_symbol_table;
    while (local_sym)
        local_sym = local_sym->next;
    local_var = local_sym->variable;
    while (local_var)
    {
        if (strcmp(local_var->name, variable->name) == 0)
        {
            printf("redefinition error\n");
            exit(1);
        }
        local_var = local_var->next;
    }
}

void    semantic_analysis(t_token *tokens)
{
    t_token *list;
    int     counter;

    counter = 0;
    list = tokens;
    while (list)
    {
        if (variable_or_function(list) == VARIABLE)
            create_variable(list);
        if (strcmp(vlist->name, "{") == 0)
            printf("create scope\n"); 
        list = list->next;
    }
}


int     main(void)
{
    t_token *list;
    char test[] = "char *hello_world = "42";\n\nint main(void) {\n\tprintf(\"%%s\");\n\treturn (0);\n}\n";
    
    list = lexer(test);
    printf("%s\n", test);
    return (0);
}








