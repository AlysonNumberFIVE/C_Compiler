
#include "../inc/compiler.h"

/*
typedef struct  s_functin_table
{
    char *function_name;
    char *datatype;
    int depth;
    char **datatype_list;
    struct s_function_table *next;
}   t_function;
*/

t_function  *new_function(char *function_name, char **variable_types,
        char *datatype, int depth)
{
    t_function  *function;

    function = (t_function *)malloc(sizeof(t_function));
    function->function_name = strdup(function_name);
    function->datatype_list = variable_types;
    function->datatype = strdup(datatype);
    function->depth = depth;
    function->next = NULL;
    return (function);
} 

t_function  *add_function(t_function *function_list, char *function_name,
        char **variable_types, char *dataype, int depth)
{
    t_function  *new_funct;
    
    new_funct = function_list;
    while (new_funct->next)
        new_funct = new_funct->next;
    new_funct->next = new_function(function_name, avriable_types,
        datatype, depth);
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

