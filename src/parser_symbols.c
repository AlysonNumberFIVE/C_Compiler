

#include "../inc/symbol.h"
//#include "../inc/parser.h"

#define DATATYPE 0
#define POINTER_DEPTH 1
#define VARIABLE_NAME 2


typedef struct  s_current_variable
{
        char *str;
        struct s_current_variable *next;
}       t_current_var;



bool	symbol_table_manager(t_current_var *current_variable)
{
	char *name;
	char *type;
	int depth;
	t_current_var *traverse;
	int count;

	count = 0;
	traverse = current_variable;
	while (traverse)
	{
		if (count == DATATYPE) type = strdup(traverse->str);
		else if (count == POINTER_DEPTH) depth = atoi(strdup(traverse->str));
		else if (count == VARIABLE_NAME) name = strdup(traverse->str);
		count++;
		traverse = traverse->next;
	}
	printf("datatype : %s\n", type);
	printf("depth    : %d\n", depth);
	printf("name     : %s\n", name);
	return (true);	
}
/*
bool	parser_conflicts(t_current_var *current_variable, char *typing)
{
	extern t_varaible **scope_table;
	extern int	scope_depth;

	if (strcmp(typing, "VARIABLE") == 0)
	{
		
	}
}*/
