

#include "../inc/compiler.h"

t_function_table    *function_talbe = NULL;

bool    is_legal_var_or_funct(t_token *token)
{
    if (assert_first_order(token) == true ||
       assert_second_order(token) == true)
        return (true);
    return (false);
}

void    semantic_analysis(t_token *token)
{
    t_scope             *scope;
    bool                scope_head;
    t_token             *list;
    int                 function_type;

    if (assert_first_order(token) == false ||
       assert_second_order(token) == false)
        return ;
    list = token;
    while (list)
    {
        if (is_legal_var_or_funct(list) == true)
        {
            function_type = semantic_variable_function(list);
        }
    }
}
