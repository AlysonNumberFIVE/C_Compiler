

#include "../inc/token.h"
#include "../inc/compiler.h"

typedef struct s_fvar
{
    char            *datatype;
    char            *var_name;
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


bool    assert_label(t_symbol *variables, char *var_name)
{
    t_symbol    *trav;

    trav = variables;
    while (trav)
    {
        if (strcmp(trav->name, var_name) == 0)
            return (true);
        trav = trav->next;
    }
    return (false);
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
    extern char first_order[33][9];
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
        depth++;
    return (depth);
}

t_fvar    *function_datatype_list(t_token *list)
{
    bool    controller;
    int     counter;
    char    *datatype;
    int     depth;
    char    *name;

    depth = 0;
    counter = 0;
    datatype = NULL;
    controller = false;
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
        else if (counter == 3 && strcmp(list->name, ",") == 0)
        {
            counter = 0;
            // create variable.
        }
        list = list->next;
    }
}

char    *datatype_name(char *name, char *to_add)
{
    char    *string;

    string = join(name, to_add);
    free(name);
    name = join(string, " ");
    free(string);
    return (name);
}
/*
void    create_function_block(declaration functions)
{

}
*/
t_declaration     *init_declaration(void)
{
    t_declaration *new;

    new = (t_declaration *)malloc(sizeof(t_declaration));
    new->datatype = NULL;
    new->datasize = 0;
    new->ptr_depth = 0;
    new->name = NULL;
    return (new);
}

void    print_declaration(t_declaration *function)
{
    printf("name : %s\n", function->name);
    printf("datatype : %s\n", function->datatype);
    printf("datasize: %d\n", function->datasize);
    printf("ptr_depth: %d\n", function->ptr_depth);
}


void    semantic_analysis(t_token *tokens)
{
    t_token *list;
    int counter;
    t_declaration *function;
    char *datatype;

    datatype = NULL;
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
        else if (counter == 3 && strcmp(list->type, "OPENBRACE") == 0)
        {
            function->variables = function_datatype_list(list);
            break;
        }
        list = list->next;
    }
    
}

int     main(int argc, char **argv)
{
    char *file = file_content(argv[1]);
    t_token *list = lexer(file);


    return (0);

}



