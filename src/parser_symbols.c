

#include "../inc/token.h"
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



void		free_fcall(t_fcall *call)
{
	t_token *trav;
	int i;

	i = 0;
	free(call->name);
	while (call->params)
	{
		trav = call->params;
		call->params = call->params->next;
		free(trav->name);
		free(trav->type);
		free(trav->filename);
		free(trav);	
	}
	free(call);
}

t_fcall		*add_call_params(t_fcall *call, t_token *param)
{
	call->params = push_token(call->params, param->name, param->type, param->line, param->filename);
	return (call);
}

t_fcall		*create_function_call(char *name)
{
	t_fcall *call;

	call = (t_fcall *)malloc(sizeof(t_fcall));
	call->name = strdup(name);
	call->params = NULL;
	return (call);
}

t_function	*search_function(char *name)
{
	extern t_function	*functions;
	t_function		*function;

	function = functions;
	while (function)
	{
		if (strcmp(function->name, name) == 0)
			return (function);
		function = function->next;
	}
	return (NULL);
}

int		verify_function_call(t_fcall *fcall)
{
	t_function	*against;
	t_token		*trav;
	t_variable	*variable;
	t_variable	*fparam;
	extern int	asterisk_count;

	against = search_function(fcall->name);	
	if (!against)
	{
		printf("Function doesn't exist error\n");
		return (1);
	}
	trav = fcall->params;
	fparam = against->parameters;
	while (trav && fparam)
	{
		if (strcmp(trav->type, "LITERAL") == 0)
		{
			if (!(fparam->depth == 1 && strcmp(fparam->type, "char") == 0))
			{
				printf("parameter error with LITERALS\n");
				return (2);
			}
		}
		else if (strcmp(trav->type, "NUM") == 0)
		{
			if (!(fparam->depth == 0 && strcmp(fparam->type, "int") == 0))
			{
				printf("parameter error with NUMbers\n");
				return (3);
			}
		}
		else if (strcmp(trav->type, "ID") == 0)
		{
			variable = search_variable(trav->name);
			printf("v type : %s f type : %s\n", variable->type, fparam->type);
			printf("v depth : %d f depth : %d\n", variable->depth, fparam->depth);
			asterisk_count = 0;
			if (variable->depth != fparam->depth)
			{	 
				printf("depth mismatch\n");
				return (4);
			}
			if (strcmp(variable->type, fparam->type) != 0) 
			{
				printf("datatype mismatch\n");	
				return (4);
			}
		}
		fparam = fparam->next;
		trav = trav->next;
	}
	if (fparam || trav)
	{
		printf("parameter length error\n");
		return (5);
	}
	return (0);
}

t_variable	*search_variable(char *name)
{
	t_variable		*variable;
	extern t_variable	**scope_table;
	extern int		scope_depth;
	int			counter;
	
	if (!scope_table)
		return (false);
	counter = scope_depth;
	while (counter > -1)
	{
		variable = scope_table[counter];
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

void	print_all_vars(void)
{
	extern int scope_depth;
	extern t_variable **scope_table;
	int count = scope_depth;
	t_variable *trav;

	if (!scope_table)
		return ;
	printf("print all vars\n");
	while (count > -1)
	{
		trav = scope_table[count];
		if (!trav) return ;
		while (trav)
		{
			printf("%s ", trav->name);
			trav = trav->next;
		}
		printf("\n\n");
		count--;
	}
	printf("count\n");
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
				printf("function found : %s\n", name);
				return (0);
			}
			function = function->next;
		}
		printf("function not found\n");
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
		printf("add to table %s\n", name);
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
			add_variable_to_table(name, type, depth);
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

	name = NULL;
	type = NULL;
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
	if (name) this_var = strdup(name);
	if (name && type)
	{
		flag = search_for_variable(name, type, depth, typing);
	}
	if (flag > 0) return (flag);
	if (traverse)
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
