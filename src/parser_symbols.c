

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
	if (!current_variable)
		return (false);
	traverse = current_variable;
	while (traverse)
	{
		printf(" %s | ", traverse->str);
		if (count == DATATYPE) type = strdup(traverse->str);
		else if (count == POINTER_DEPTH) depth = atoi(strdup(traverse->str));
		else if (count == VARIABLE_NAME) 
		{
			name = strdup(traverse->str);
			break;
		}
		count++;
		traverse = traverse->next;
	}
	printf("\n\n");
	printf("datatype : %s\n", type);
	printf("depth    : %d\n", depth);
	printf("name     : %s\n", name);
	traverse = traverse->next;
	if (traverse)
	{
		printf("\nVARIABLES\n");
		count = 0;
		while (traverse)
		{
			if (count == DATATYPE) type = strdup(traverse->str);
			else if (count == POINTER_DEPTH) depth = atoi(strdup(traverse->str));
			else if (count == VARIABLE_NAME)
			{
				name = strdup(traverse->str);
				printf("\tdatatype   : %s\n", type);
				printf("\tdepth      : %d\n", depth);
				printf("\tname       : %s\n", name);
				printf("\n\n");
			}
			if (count == 2)
				count = 0;
			else
				count++;
			traverse = traverse->next;
		}
	}
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
