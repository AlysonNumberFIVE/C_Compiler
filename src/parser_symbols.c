

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

//t_function	*functions = NULL;
t_str_uni	*structs_unions = NULL;

t_variable	*search_variable(char *name)
{
	t_variable		*variable;
	extern t_variable	**scope_table;
	extern int		scope_depth;
	int			counter;
	
	if (!scope_table)
		return (false);
	counter = 0;
	while (counter > -1)
	{
		variable = scope_table[scope_depth];
		while (variable)
		{
			if (strcmp(variable->name, name) == 0)
				return (variable);
			variable = variable->next;
		}
		counter--;
	}
	return (NULL);
}

int	search_for_label(char *name, char *next_token)
{
	extern t_function	*functions;
	extern t_variable	**scope_table;
	extern int		scope_depth;
	t_variable		*traverse;
	t_function		*function;
	int			counter;

	counter = 0;
	if (next_token && strcmp(next_token, "(") == 0)
	{
		function = functions;
		while (function)
		{
			if (strcmp(function->name, name) == 0)
			{
				return (0);
			}
			function = function->next;
		}
		return (1);
	}
	else 
	{
		if (!scope_table)
			return (2);
		counter = scope_depth;
		while (counter > -1)
		{	
			traverse = scope_table[counter];
			while (traverse)
			{
				if (strcmp(traverse->name, name) == 0)
					return (0);
				traverse = traverse->next;
			}
			counter--;
		}
		return (2);
	}
	return (0);
}

int 	search_for_variable(char *name, char *type, int depth, char *typing)
{
	t_function *function;
	t_variable *variable;
	extern t_variable **scope_table;
	extern t_function *functions;
	extern int 	scope_depth;	
	bool flag;
	
	flag = false;
	if (typing && strcmp(typing, "FUNCTION") == 0)
	{
		function = functions;
		while (function)
		{
			if (strcmp(function->name, name) == 0)
			{
				flag = true;
				break;
			}
			function = function->next;
		}
		if (flag == true) return (1);
		else functions = push_function(functions, name, type, depth);
	}
	else if (typing && strcmp(typing, "VARIABLE") == 0 || strcmp(typing, "ASSIGN") == 0)
	{
		if (add_variable_to_table(name, type, depth) == false)
		{
			return (1);
		}
	}
	return (0);
}

t_variable	*variable_chain(t_current_var *traverse, char *function_name)
{
	int count;
	char *name;
	char *type;
	int depth;
	t_variable *var;
	extern t_function *functions;
	
	var = NULL;
	count = 0;
	while (traverse)
	{
		if (count == DATATYPE) type = strdup(traverse->str);
		else if (count == POINTER_DEPTH) depth = atoi(traverse->str);
		else if (count == VARIABLE_NAME)
		{
			name = strdup(traverse->str);
			var = push_variable(var, name, type, depth); 
			free(name);
			free(type);
			functions = add_function_params(functions, function_name, var);
		}
		if (count == 2)
			count = 0;
		else 
			count++;
		traverse = traverse->next;
	}
}

int	symbol_table_manager(t_current_var *current_variable, char *typing)
{
	char *name;
	char *type;
	int depth;
	t_current_var *traverse;
	int count;
	int flag;
	extern char *this_var;
	extern t_function *functions;

	count = 0;
	flag = 0;
	if (!current_variable)
		return (false);
	traverse = current_variable;
	while (traverse)
	{
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
	this_var = strdup(name);
	flag = search_for_variable(name, type, depth, typing);
	free(name);
	free(type);
	if (flag > 0) return (flag);
	traverse = traverse->next;
	if (traverse)
	{
		variable_chain(traverse, this_var);
	}
	return (0);	
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
