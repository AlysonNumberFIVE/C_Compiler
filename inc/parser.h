

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

bool	parser(t_token *tokens);
bool	is_datatype_correct(t_pstack *stack, int datatype_len);
char 	**psplit(char *str, char c);

#endif
