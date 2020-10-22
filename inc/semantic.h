


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


typedef struct s_struct
{
        char *struct_name;
        int struct_param_number;
	t_fvars  **variables;
        struct s_struct *structs;
        struct s_struct *next;
}       t_struct;

typedef struct  s_function_list
{
	char	*type;
	int	depth;
        char	*function_name;
        t_fvars **parameters;
	int 	param_number;
	int 	defined_flag;
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

bool		does_variable_type_match(char *str, char *str2);
t_stack		*new_stack(int scope_name);
t_stack		*add_stack(t_stack *head, int scope_name);
t_stack		*push_stack(t_stack *head, int scope_name);
t_stack		*pop_stack(t_stack *head);
char		*join_with_space(char *first, char *second);
bool		is_valid_equation(t_token *tokens, char *end_token);
char		*value_checker(t_token *components);


t_token		*semantic_for(char *prev, t_token *token, t_hashtable *ff_list);
t_token		*semantic_while(char *prev, t_token *token, t_hashtable *ff_list);
t_token		*semantic_if(char *prev_name, t_token *token, t_hashtable *ff_list);

t_stack		*push_stack(t_stack *head, int scope_name);
t_token		*struct_loop(t_token *val);

t_fvars         **add_to_param_list(t_fvars **array, t_fvars *to_add, size_t list_size);
void 		print_structs(t_struct *all_structs);
bool		does_function_exist(char *name);
bool    	assert_parameter_correctness(t_token *type, char *function_name);
t_function	*get_function(char *name);
bool		handle_struct_dereferencing(t_token *token);
bool		set_defined(char *function_name, int def_type);
bool		handle_redefinition(t_function *original, t_fvars **new_params, int new_count,
	char *ending_tag);
bool		validate_function(t_token *token);
bool		check_next_token(t_hashtable *ff_list, char *next_token, char *current_token);


#endif




