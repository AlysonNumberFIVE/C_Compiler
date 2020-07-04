
#include "../inc/semantic.h"
#include "../inc/token.h"
#include "../inc/compiler.h"

#define DECLARATION 1
#define DEFINITION  2
#define ASSIGN      3
typedef struct s_fvar
{
    char            *datatype;
    char            *var_name;
    int             depth;
    struct s_fvar   *next;
}   t_fvar;

typedef struct function_delcaration
{
    char    *datatype;
    int     datasize;
    int     ptr_depth;
    char    *name;
    struct s_fvar *variables;
}   t_declaration;

/*
char    *datatype_name(char *name, char *to_add);
bool    assert_label(t_symbol *variables, char *var_name)
bool    assert_second_order(char *to_check)
bool    assert_first_order(char *to_check)
int     determine_pointer_depth(t_token *list);
*/

t_fvar   *new_fvar(char *datatype, char *var_name, int depth)
{
    t_fvar  *new;

    new = (t_fvar *)malloc(sizeof(t_fvar));
    new->datatype = strdup(datatype);
    new->var_name = strdup(var_name);
    new->depth = depth;
    new->next = NULL;
    return (new);
}

t_fvar  *add_fvar(t_fvar *new, char *datatype, char *var_name, int depth)
{
    t_fvar  *add;

    add = new;
    while (add->next)
        add = add->next;
    add->next = new_fvar(datatype, var_name, depth);
    return (add);
}

t_fvar  *push_fvar(t_fvar *new, char *datatype, char *var_name, int depth)
{
    t_fvar  *trav;

    trav = new;
    if (trav == NULL)
        trav = new_fvar(datatype, var_name, depth);
    else
    {
        trav = add_fvar(new, datatype, var_name, depth);
        trav = new;
    }
    return (trav);
}


t_fvar    *function_datatype_list(t_token *list)
{
    bool    controller;
    int     counter;
    char    *datatype;
    int     depth;
    char    *name;
    t_fvar  *variables;

    depth = 0;
    counter = 0;
    datatype = (char *)malloc(sizeof(char));
    controller = false;
    variables = NULL;
    list = list->next;
    while (strcmp(list->name, ")") != 0 && list)
    {
        if (counter == 0 && assert_first_order(list->name) == true)
        {
            counter++;
            datatype = datatype_name(datatype,list->name);
        }
        else if (counter <= 1 && assert_second_order(list->name) == true)
        {
            counter = 2;
            datatype = datatype_name(datatype, list->name);
        }
        else if (counter == 2 && strcmp(list->name, "*") == 0)
            depth = determine_pointer_depth(list);
        else if (counter == 2 && strcmp(list->type, "ID") == 0)
        {
            name = strdup(list->name);
            counter++;
        }
        if (counter == 3)
        {
            printf("datatype : %s\n", datatype);
            printf("depth : %d\n", depth);
            printf("name : %s\n", name);
            variables = push_fvar(variables, datatype, name, depth);
            datatype = NULL;
            datatype = (char*)malloc(sizeof(char));
            printf("\n\n\n");
            counter = 0;
        }
        list = list->next;
    }

   // printf("variables is %s\n", variables->var_name);
    return (variables);
}


t_declaration     *init_declaration(void)
{
    t_declaration *new;

    new = (t_declaration *)malloc(sizeof(t_declaration));
    new->datatype = NULL;
    new->datasize = 0;
    new->ptr_depth = 0;
    new->name = NULL;
    new->variables = NULL;
    return (new);
}

void    print_declaration(t_declaration *function)
{
    printf("name : %s\n", function->name);
    printf("datatype : %s\n", function->datatype);
    printf("datasize: %d\n", function->datasize);
    printf("ptr_depth: %d\n", function->ptr_depth);
    t_fvar  *var;
    var = function->variables;
    while (var)
    {
        printf("\n\tname: %s\n", var->var_name);
        printf("\ttype: %s\n", var->datatype);
        var = var->next;
    }
}


int    semantic_variable_function(t_token *tokens)
{
    t_token *list;
    int counter;
    t_declaration *function;
    char *datatype;
    bool is_function;

    is_function = false;
    datatype = (char *)malloc(sizeof(char));
    function = init_declaration();
    counter = 0;
    list = tokens;
    while (list)
    {
        if (counter == 0 && assert_first_order(list->name) == true)
        {
            datatype = datatype_name(datatype, list->name);
            counter++;
        }
        else if (counter <= 1 && assert_second_order(list->name) == true)
        {
            datatype = datatype_name(datatype, list->name);
            counter = 2;
        }
        else if (counter == 2 && strcmp(list->name, "*") == 0)
             function->ptr_depth = determine_pointer_depth(list);
        else if (counter == 2 && strcmp(list->type, "ID") == 0)
        {
            function->name = strdup(list->name);
            counter++;
        }
        else if (counter == 3 && strcmp(list->name, "(") == 0)
        {
            is_function = true;
            function->variables = function_datatype_list(list);
            break;
        }
        else if (counter == 3 && strcmp(list->name, "=") == 0)
            break ;
        list = list->next;
    }
    function->datatype = datatype;
    print_declaration(function);
    if (strcmp(list->name, ";") == 0) 
        return (DECLARATION);
    else if (strcmp(list->name, "{") == 0)
        return (DEFINITION);
    else if (strcmp(list->name, "=") == 0)
        return (ASSIGN);
    return (-1);
}





int     main(int argc, char **argv)
{
    char *file = file_content(argv[1]);
    t_token *list = lexer(file);
    t_token *print;

    print = list;
    while (print)
    {
        printf("%s : %s\n", print->name, print->type);
        print = print->next;
    }
    int value = semantic_variable_function(list);
    printf("value is %d\n", value);
    return (0);
}


