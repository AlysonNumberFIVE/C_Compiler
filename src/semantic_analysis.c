
#include "../inc/semantic.h"
#include "../inc/token.h"
#include "../inc/symbol.h"
#include "../inc/compiler.h"

#define FUNCTION 1
#define VARIABLE 2

t_scope             *g_symbol_table = NULL;
t_function_table    *function_table = NULL;
t_variable          *g_var = NULL;

t_token    *skip_stars(t_token *token)
{
    while (token && strcmp(token->name, "*") == 0)
        token = token->next;
    if (token)
        return (token);
    return (NULL);
}

int     variable_or_function(t_token *tokens)
{
    t_token     *list;
    t_token     *head;

    list = tokens;
    if (assert_first_order(list->name) == true)
    {
        if (assert_second_order(list->next->name) == true)
            list = list->next->next;
    }
    else if (assert_second_order(list->name) == true)
        list = list->next;
    else
        return (-1);
    if (list && strcmp(list->name, "*") == 0)
        list = skip_stars(list);
    if (strcmp(list->type, "ID") == 0)
        list = list->next;
    if (strcmp(list->name, "(") == 0)
        return (1);
    if (strcmp(list->name, ";") == 0 || strcmp(list->name, "=") == 0)
    {
        printf("2\n");
        return (2);
    }
    return (-1);
}

t_token   *create_variable(t_token **list)
{
    t_variable  *variable;
    t_scope     *local_sym;
    t_token     *token;
    t_variable  *var;
    
    local_sym = g_symbol_table;
    while (local_sym->next)
        local_sym = local_sym->next;

    local_sym->variables = g_var; 
    token = *list;
    variable = save_variable(&token, ";");
    
    g_var = push_variable(g_var, variable->name, variable->datatype,
        variable->value);
    

    //printf("g_var->name is %s\n", g_var->name);
    free(variable->name);
    free(variable->datatype);
    free(variable->value);
    free(variable);
    return (token);
}

void    semantic_analysis(t_token *tokens)
{
    t_token *list;
    int     counter;
    extern t_scope *g_symbol_table;
    int     value;

    counter = 0;
    list = tokens;
    while (list)
    {
       value = variable_or_function(list);
       if (value == 2)
       {
           create_variable(&list);
       }
       else if (value == 1)
       {
           semantic_function(&list);
       }
       if (strcmp(list->name, "{") == 0)
       {
           printf("creating new scope\n");
           g_symbol_table->variables = copy_variables(g_var);
       }
       list = list->next;
    }
}


int     main(void)
{
    t_token *list;

    g_symbol_table = (t_scope *)malloc(sizeof(t_scope));
    g_symbol_table->depth = 0;
    g_symbol_table->variables = NULL;
    g_symbol_table->next = NULL;
    //char test[] = "char *hello_world = \"42\";int again = 42;\nvoid *value = NULL;\nchar *new_list(char *name);"; 
    char test[] = "char **split(char *first, char second);char *str = 42;\nint i = 0;\nchar *string = \"hello world\";\nint main(void){return (0);}";
    list = lexer(test);
    semantic_analysis(list);
    t_variable  *variables;
    printf("%s\n", test);
    variables = g_symbol_table->variables;
    while (variables)
    {
        printf("var >>> is %s\n", variables->name);
        variables = variables->next;
    }
    return (0);
}








