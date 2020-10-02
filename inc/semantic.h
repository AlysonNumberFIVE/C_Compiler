


#ifndef _SEMANTIC_
#define _SEMANTIC_

#include "compiler.h"

typedef struct	s_function_var
{
	char	*type;
	char	*name;
	size_t	size;
	int	depth;
	char	*value;
}	t_fvars;

typedef struct  s_function_list
{
        char	*function_name;
        t_fvars **parameters;
	int 	param_number;
        struct s_function_list *next;
}       t_function;


bool    semantic_analysis(t_token *tokens);
char    *datatype_name(char *name, char *to_add);
bool    assert_second_order(char *to_check);
bool    assert_first_order(char *to_check);
int     determine_pointer_depth(t_token *list);
//int     semantic_function(t_token *tokens);
t_stack *pop_stack(t_stack *top);
t_stack *push_stack(t_stack *head, char *function_name);
int     semantic_function(t_token **tokens);


t_function *new_function(char *function_name);
t_function      *add_function(t_function *head, char *function_name);
t_function      *push_function(t_function *head, char *function_name);

#endif
