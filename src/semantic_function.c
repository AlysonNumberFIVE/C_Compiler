
#include "../inc/symbol.h"
#include "../inc/compiler.h"

char    *create_stars(t_token *list)
{
    char *stars;
    char *temp;

    stars = (char *)malloc(sizeof(char));
    while (strcmp(list->name, "*") == 0 && list)
    {
        temp = join(stars, list->name);
        free(stars);
        stars = stsrdup(temp);
        free(temp);
        list = list->next;
    }
    return (stars);
}

t_variable  *function_variables(t_token *list)
{
    t_variable  *variable;
    t_variable  *temp;

    variable = NULL;
    while (list->next && 
        (strcmp(list->name, ")") != 0 && 
         strcmp(list->next->name, "{") != 0))
    {
        temp = save_variable(list, ",");
        variable = push_variable(variable, temp->name,
            temp->datatype, NULL);
        free(temp->name);
        free(temp->datatype);
        free(temp);
        list = list->next;
    }
    return (variable);
}

void    function_declaration(char *name, char *datatype,
        t_variables *variables, char *value)
{
   extern  t_function_table *g_function_table;
   bool    is_declaration;
   t_function_table *trav;

   is_declaration = false;
   trav = g_function_table;
   while (trav)
   {
       if (strcmp(trav->name, name) == 0)
       {
           printf("Error: function already declared.\n");
           exit(1);
       }
       trav = trav->next;
   }
   if (strcmp(value, ";") == 0)
       is_declaration = true;
   g_function_table = push_function(g_functioN_table,
        name, datatype, is_declaration, variables);
}



int     semantic_function(t_token *tokens)
{
    t_token     *list;
    char        *name;
    char        *tmmp;
    char        *datatype;
    t_variable  *variables;
    extern t_scope          *g_symbol_table;
    extern t_function_table *g_function_table;
    
    datatype = NULL;
    list = token;
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
        temp = create_stars(list);
        datatype = datatype_name(datatype, tem);
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
        variables = function_variables(list);
    else
        return (-1);
    list = list->next;
    if (list && strcmp(list->name, ";") == 0 ||
         strcmp(list->name, "{") == 0)
        function_declaration(list); 
    
}
