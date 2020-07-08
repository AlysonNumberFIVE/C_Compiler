
#include "../inc/symbol.h"
#include "../inc/compiler.h"
#include "../inc/semantic.h"

char    *create_stars(t_token **token)
{
    char *stars;
    char *temp;
    t_token *list;

    list = *token;
    stars = (char *)malloc(sizeof(char));
    while (strcmp(list->name, "*") == 0 && list)
    {
        temp = join(stars, list->name);
        free(stars);
        stars = strdup(temp);
        free(temp);
        list = list->next;
    }
    *token = list;
    return (stars);
}

t_variable  *function_variables(t_token **tokens)
{
    t_variable  *variable;
    t_variable  *temp;
    t_token     *list;

    list = *tokens;
    list = list->next;
    variable = NULL;
    while (list->next && 
        (strcmp(list->name, ")") != 0 && 
            (strcmp(list->next->name, "{") != 0 || 
             strcmp(list->next->name, ";") != 0)))
    {
        printf("this is %s\n", list->name);
        if (strcmp(list->name, ";") == 0)
            break ;
        temp = save_variable(&list, ",");
        printf("parameter name is %s\n", temp->name);
        variable = push_variable(variable, temp->name,
            temp->datatype, NULL);
        free(temp->name);
        free(temp->datatype);
        free(temp);
        list = list->next;
    }
    *tokens = list;
    return (variable);
}

void    function_declaration(char *name, char *datatype,
        t_variable *variables)
{
   extern  t_function_table *function_table;
   bool    is_declaration;
   char     *value;
   t_function_table *trav;

   is_declaration = false;
   trav = function_table;
   while (trav)
   {
       if (strcmp(trav->function_name, name) == 0)
       {
           printf("Error: function already declared.\n");
           exit(1);
       }
       trav = trav->next;
   }
   if (strcmp(value, ";") == 0)
       is_declaration = true;
   function_table = push_function(function_table,
        name, datatype, is_declaration, variables
    );
}



int     semantic_function(t_token **tokens)
{
    t_token     *list;
    char        *name;
    char        *temp;
    char        *datatype;
    t_variable  *variables;
    extern t_scope          *g_symbol_table;
    extern t_function_table *function_table;
    
    datatype = (char *)malloc(sizeof(char));
    bzero(datatype, sizeof(char));
    list = *tokens;
    if (assert_first_order(list->name) == true)
    {
        datatype = datatype_name(datatype, list->name);
        if (assert_second_order(list->next->name) == true)
        {
            datatype = datatype_name(datatype, list->next->name);
            list = list->next->next;
        }
    }
    else if (assert_second_order(list->name) == true)
    {
        datatype = datatype_name(datatype, list->name);
        list = list->next;
    }
    if (list && strcmp(list->name, "*") == 0)
    {
        temp = create_stars(&list);
        datatype = datatype_name(datatype, temp);
        free(temp);
    }
    if (list && strcmp(list->type, "ID") == 0)
    {
        name = strdup(list->name);
        list = list->next;
    }
    else 
        return (-1);
    if (list && strcmp(list->name, "(") == 0)
    {
        if (list->next && strcmp(list->next->name, "void") == 0)
            variables = NULL;
        else
            variables = function_variables(&list);
    }
    else
        return (-1);
   // list = list->next;
     
    if (list && (strcmp(list->name, ";") == 0 ||
         strcmp(list->name, "{")) == 0)
        function_declaration(name, datatype, variables); 
    printf("list is %s\n", list->name);
    *tokens = list;

}
