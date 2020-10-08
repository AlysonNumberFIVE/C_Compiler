


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
	char	*type;
	int	depth;
        char	*function_name;
        t_fvars **parameters;
	int 	param_number;
        struct s_function_list *next;
}       t_function;

typedef struct	s_sstack
{
	int scope_name;
	struct s_sstack *next;
	struct s_sstack *prev;
}	t_stack;

bool    semantic_analysis(t_token *tokens);
char    *datatype_name(char *name, char *to_add);
bool    assert_second_order(char *to_check);
bool    assert_first_order(char *to_check);
int     determine_pointer_depth(t_token *list);
//int     semantic_function(t_token *tokens);
//t_stack *pop_stack(t_stack *top);
//t_stack *push_stack(t_stack *head, char *function_name);
int     semantic_function(t_token **tokens);


t_function *new_function(char *function_name, char *type, int depth);
t_function      *add_function(t_function *head, char *function_name, char *type, int depth);
t_function      *push_function(t_function *head, char *function_name, char *type, int depth);

t_fvars         *create_new_parameter(char *name, char *type, int depth);
void            param_free(t_fvars *parameter);
t_function      *new_parameter(t_function *all_functions, char *function_name, t_fvars *new_param);
void		print_functions(t_function *functions);


t_stack		*new_stack(int scope_name);
t_stack		*add_stack(t_stack *head, int scope_name);
t_stack		*push_stack(t_stack *head, int scope_name);
t_stack		*pop_stack(t_stack *head);

bool		is_valid_equation(t_token *tokens, char *end_token);
char		*value_checker(t_token *components);
t_token		*semantic_for(char *prev, t_token *token);
t_stack		*push_stack(t_stack *head, int scope_name);
t_token		*struct_loop(t_token *val);

#endif



