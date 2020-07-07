

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


char    *equ_content(t_token **list)
{
    char    *value;
    char    *str;
    char    *temp;
    t_token *token;

    token = *list;
    str = NULL;
    if (token->next)
        token = token->next;
    else 
        return (NULL);
    temp = (char *)malloc(sizeof(char));
    while (token && strcmp(token->name, ";") != 0)
    {
        str = join(temp, token->name);
        free(temp);
        temp = strdup(str);
        free(str);
        token = token->next;
    }
    value = strdup(temp);
    free(temp);
    *list = token;
    return (value);
}

t_variable    *save_variable(t_token **token, char *stop)
{
    t_variable  *var;
    t_token     *list;
    char        *name;
    char        *datatype;
    char        *value;
    int         counter;
    char        *star;

    list = *token;
    counter = 0;
    var = NULL;
    star = NULL;
    value = NULL;
    datatype = NULL;
    name = NULL;
    if (assert_second_order(list->name) == false)
        if (assert_first_order(list->name) == false)
           return (NULL);
    datatype = (char *)malloc(sizeof(char));
    bzero(datatype, sizeof(char));
        if (counter == 0 && assert_first_order(list->name) == true)
        {
            datatype = datatype_name(datatype, list->name);
            counter++;
        }
        else if (counter <= 1 && assert_second_order(list->name) == true)
        {
            datatype = datatype_name(datatype, list->name);
            list = list->next;
            counter = 2;
        }
        if (counter == 2 && strcmp(list->name, "*") == 0)
        {
            star = pointer_depth(&list);
            datatype = datatype_name(datatype, star);
            free(star);
            counter++;
        }
        if (counter >= 2 && strcmp(list->type, "ID") == 0)
        {
            name = strdup(list->name);
            counter = 3;
            list = list->next;
        }
        if (counter == 3 && strcmp(list->name, "=") == 0)
            value = equ_content(&list);
         else if (counter == 3 && strcmp(list->name, stop) != 0)
        {
            exit(1);
        }
         printf("list after equ_content %s\n", list->name);
    if (name && datatype)
        var = push_variable(var, name, datatype, value);
    printf("name is %s\n", name);
    printf("datatype is %s\n", datatype);
    printf("value is %s\n", value);
    free(datatype);
    free(name);
    if (value)
        free(value);
    *token = list;
    return (var);
}
/*
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
}*/
