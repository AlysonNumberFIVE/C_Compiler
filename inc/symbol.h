


#ifndef SYMBOL_H
#define SYMBOL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct	s_variable
{
	char *name;
	char *type;
	int depth;
	struct s_variable *next;
}	t_variable;

typedef struct	s_function
{
	char *name;
	char *type;
	int depth;
	t_variable *parameters;
	struct s_function *next;
}	t_function;

typedef struct 	s_structs_or_union
{
	char *name;
	t_variable *members;
	struct s_structs_or_union *next;
}	t_str_uni;


typedef struct	s_function_call
{
	char *name;
	t_token	*params;
}	t_fcall;

t_function      *push_function(t_function *function, char *name, char *type, int depth);
t_str_uni       *push_struct_union(t_str_uni *struct_union, char *name);
t_variable      *push_variable(t_variable *variable, char *name, char *type, int depth);
void            free_variables(t_variable *variable);
t_function      *add_function_params(t_function *functions, char *name, t_variable *params);
t_str_uni       *add_struct_members(t_str_uni *struct_union, char *name, t_variable *params);
bool            add_variable_to_table(char *name, char *type, int depth);
bool		drop_scope_block(void);
void		new_scope_block(void);
bool    	does_variable_exist(char *name, char *typing);
int		search_for_label(char *name, char *next_token);
t_variable	*search_variable(char *name);

#endif
