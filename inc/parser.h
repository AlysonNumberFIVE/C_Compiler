

#ifndef PARSER_H
#define PARSER_H
#include "compiler.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_parse_stack
{
	char *token;
	char *type;
	char *construct;
	struct s_parse_stack *next;
	struct s_parse_stack *prev;
}	t_pstack;

typedef struct	s_current_variable
{
	char *str;
	struct s_current_variable *next;
}	t_current_var;

bool	parser(t_token *tokens);
bool	is_datatype_correct(t_pstack *stack, int datatype_len);
char 	**psplit(char *str, char c);
t_current_var *push_curr_var(t_current_var *head, char *name);
void	free_curr_var(t_current_var *head);
bool	symbol_table_manager(t_current_var *current_variable, char *typing);
bool	false_error(t_token *token, int message);

bool	evaluate_equation(void);
bool    equ_tokens(char *name);
bool    sum_tokens(char *name);

bool	evaluate_literal(t_token *token);

#endif
