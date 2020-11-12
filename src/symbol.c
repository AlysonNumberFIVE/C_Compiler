

#include "../inc/symbol.h"


// function pushing

t_variable	**scope_table = NULL;
int		scope_depth = 0;

t_function	*new_function(char *name, char *type, int depth)
{
	t_function	*new_function;

	new_function = (t_function *)malloc(sizeof(t_function));
	new_function->name = strdup(name);
	new_function->parameters = NULL;
	new_function->type = type;
	new_function->depth = depth;
	new_function->next = NULL;
	return (new_function);
}

t_function	*add_function(t_function *function, char *name, char *type, int depth)
{
	t_function 	*traverse;

	traverse = function;
	while (traverse->next)
		traverse = traverse->next;
	traverse->next = new_function(name, type, depth);
	return (traverse);	
}

t_function	*push_function(t_function *function, char *name, char *type, int depth)
{
	t_function	*traverse;

	traverse = function;
	if (traverse == NULL)
		traverse = new_function(name, type, depth);
	else
	{
		traverse = add_function(function, name, type, depth);
		traverse = function;	
	}
	return (traverse);
}

t_str_uni	*new_struct_union(char *name)
{
	t_str_uni	*struct_union;

	struct_union = (t_str_uni *)malloc(sizeof(t_str_uni));
	struct_union->name = strdup(name);
	struct_union->members = NULL;
	struct_union->next = NULL;
	return (struct_union);
}

t_str_uni	*add_struct_union(t_str_uni *struct_union, char *name)
{
	t_str_uni	*traverse;

	traverse = struct_union;
	while (traverse->next)
		traverse = traverse->next;
	traverse->next = new_struct_union(name);
	return (traverse);
}

t_str_uni	*push_struct_union(t_str_uni *struct_union, char *name)
{
	t_str_uni	*traverse;

	traverse = struct_union;
	if (traverse == NULL)
	{
		traverse = new_struct_union(name);
	}
	else
	{
		traverse = add_struct_union(struct_union, name);
		traverse = struct_union;
	}
	return (traverse);
}

t_variable	*new_variable(char *name, char *type, int depth)
{
	t_variable	*variable;

	variable = (t_variable *)malloc(sizeof(t_variable));
	variable->name = strdup(name);
	variable->type = strdup(type);
	variable->depth = depth;
	variable->next = NULL;
	return (variable);
}

t_variable	*add_variable(t_variable *variable, char *name, char *type, int depth)
{
	t_variable	*traverse;

	traverse = variable;
	while (traverse->next)
		traverse = traverse->next;
	traverse->next = new_variable(name, type, depth);
	return (traverse);
}


t_variable	*push_variable(t_variable *variable, char *name, char *type, int depth)
{
	t_variable	*traverse;
	
	traverse = variable;
	if (traverse == NULL)
	{
		traverse = new_variable(name, type, depth); 
	}
	else
	{
		traverse = add_variable(variable, name, type, depth);
		traverse = variable;
	}
	return (traverse);
}

void		free_variables(t_variable *variable)
{
	t_variable	*traverse;

	while (variable)
	{
		traverse = variable;
		variable = variable->next;
		free(traverse->name);
		free(traverse->type);
		free(traverse);
	}
}

t_function	*add_function_params(t_function *functions, char *name, t_variable *params)
{
	t_function	*traverse;
	bool		found;

	found = false;
	traverse = functions;
	while (traverse)
	{
		if (strcmp(traverse->name, name) == 0)
		{
			found = true;
			break;
		}
		traverse = traverse->next;
	}
	if (found == true)
		traverse->parameters = params;
	return (functions);
}

t_str_uni	*add_struct_members(t_str_uni *struct_union, char *name, t_variable *params)
{
	t_str_uni	*traverse;
	bool		found;

	found = false;
	traverse = struct_union;
	while (traverse)
	{
		if (strcmp(traverse->name, name) == 0)
		{
			found = true;
			break;	
		}
		traverse = traverse->next;
	}
	if (found == true)
		traverse->members = params;
	return (struct_union);
}

bool		add_variable_to_table(char *name, char *type, int depth)
{
	int nullifier;
	t_variable *name_checker;
	int found;
	extern t_function *functions;
	t_function	*function;
	
	found = false;
	name_checker = NULL;
	nullifier = 0;
	if (scope_table == NULL)
	{
		scope_table = (t_variable **)malloc(sizeof(t_variable *) * 1000); // make dynamic someday.
		while (nullifier < 1000)
		{
			scope_table[nullifier] = NULL;
			nullifier++;
		}
	}
	else
	{
		name_checker = scope_table[scope_depth];
		while (name_checker)
		{
			if (strcmp(name_checker->name, name) == 0)
			{
				found = true;
				break;		
			}
			name_checker = name_checker->next;
		}
		if (found == false)
		{
			function = functions;
			while (function)
			{
				if (strcmp(function->name, name) == 0)
				{
					found = true;
					break;
				}
				function = function->next;
			}
		}
		if (found == true)
			return (false);
	}
	scope_table[scope_depth] = push_variable(scope_table[scope_depth], name, type, depth);
	return (true);
}

bool	drop_scope_block(void)
{
	if (scope_depth < 0)
		return (false);
	free_variables(scope_table[scope_depth]);
	scope_depth--;
	return (true);
}

void	new_scope_block(void)
{
	scope_depth++;
}
/*
bool	does_variable_exist(char *name, char *typing)
{
	t_variable	*variable;
	t_function	*function;
	
	if (strcmp(typing, "ASSIGN") == 0)
	{
		variable = scope_table[scope_depth];
		// this scope.
		while (variable)
		{
			if (strcmp(variable->name, name) == 0)
				return (true);
			variable = variable->next;
		}
		// global scope
		variable = scope_table[0];
		while (variable)
		{
			if (strcmp(variable->name, name) == 0)
				return (true);
			variable = variable->next;
		}
		// function scope
		function = functions;
		while (function)
		{
			if (strcmp(function->name, name) == 0)
				return (true);
			function = function->next;
		}
	}
	else if (strcmp(typing, "CALL") == 0)
	{
		function = functions;
		while (function)
		{
			if (strcmp(function->name, name) == 0)
				return (true);
			function = function->next;
		}
	} 
}
*/





