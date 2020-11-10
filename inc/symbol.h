


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






#endif
