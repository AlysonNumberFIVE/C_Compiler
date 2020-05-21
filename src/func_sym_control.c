
#include "../inc/compiler.h"

t_function  *new_function(char *function_name, char **variable_types)
{
    t_function  *function;

    function = (t_function *)malloc(sizeof(t_function));
    function->function_name = strdup(function_name);
    function->datatype_list = variable_types;
    function->next = NULL;
    return (function);
} 

t_function  *add_function(t_function *function_list, char *function_name,
        char **variable_types)
{
    t_function  *new_funct;
    
    new_funct = function_list;
    while (new_funct->next)
        new_funct = new_funct->next;
    new_funct->next = (t_function *)malloc(sizeof(t_function));
    new_funct->next->function_name = strdup(function_name);
    new_funct->next->datatype_list = datatype_list;
    new_funct->next->next = NULL;
    return (new_funct);
}

t_function  *push_function(t_function *function_list, char *function_name,
        char **variable_types)
{
    t_function  *new_funct;

    new_funct = function_list;
    if (new_fuct == NULL)
    {
        function_list = new_function(function_name, variable_list);
    }
    else
    {
        new_fuct = add_function(function_list, function_name, variable_list);
        new_funct = function_list;
    }
    return (new_fuct);
}

