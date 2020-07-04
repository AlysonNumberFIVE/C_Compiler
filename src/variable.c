

#include "../inc/token.h"
#include "../inc/semantic.h"
#include "../inc/compiler.h"
#include "../inc/symbol.h"

/*
typedef struct  s_variable
{
    char    *name;
    char    *datatype;
    char    *value;
    struct s_variable   *next;
}   t_variable;
*/

char    *pointer_depth(t_token **token)
{
    char    *star;
    t_token *list;

    list = *token;
    star = NULL;
    while (strcmp(list->name, "*") == 0)
    {
        star = charpush(star, list->name[0]);
        list = list->next;
    }
    *token = list;
    return (star);
}

/*
t_variable  *push_variable(t_variable *head, char *name,
            char *datatype, char *content)
*/

char    *equ_content(t_token *token)
{
    char    *value;
    char    *str;
    char    *temp;

    str = NULL;
    if (token->next)
        token = token->next;
    else 
        return (NULL);
    temp = (char *)malloc(sizeof(char));
    while (strcmp(token->name, ";") != 0)
    {
        str = join(temp, token->name);
        free(temp);
        temp = strdup(str);
        free(str);
        token = token->next;
    }
    value = strdup(temp);
    free(temp);
    return (value);
}

t_variable    *save_variable(t_token *token)
{
    t_variable  *var;
    t_token     *list;
    char        *name;
    char        *datatype;
    char        *value;
    int         counter;
    char        *star;

    list = token;
    counter = 0;
    var = NULL;
    star = NULL;
    value = NULL;
    name = NULL;
    if ( assert_second_order(list->name) == false || assert_second_order(list->name) == false)
        return (NULL);
    datatype = (char *)malloc(sizeof(char));;
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
        {
            star = pointer_depth(&list);
            datatype = datatype_name(datatype, star);
            counter++;
        }
        if (counter >= 2 && strcmp(list->type, "ID") == 0)
        {
            name = strdup(list->name);
            counter = 3;
        }
        else if (counter == 2 && strcmp(list->name, ";") == 0)
            break ;
        else if (counter == 3 && strcmp(list->name, "=") == 0)
        {
            value = equ_content(list);
            break ;
        }
        list = list->next;
    }
    if (name && datatype)
        var = push_variable(var, name, datatype, value);
    return (var);
}

int     main(void)
{
    char *testing = "char ** test = {\"42\"};";
    testing = "int i = 0;";
    t_token *tokens;
    t_variable  *var;

    tokens = lexer(testing);
    var = save_variable(tokens);
    print_variable(var);
    return (0);
}
