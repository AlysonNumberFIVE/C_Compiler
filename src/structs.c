
#include "../inc/token.h"
#include "../inc/database.h"
#include "../inc/semantic.h"
#include "../inc/compiler.h"

t_struct	*new_struct(char *struct_name)
{
	t_struct	*new;

	new = (t_struct *)malloc(sizeof(t_struct));
	new->struct_name = strdup(struct_name);
	new->variables = NULL;
	new->structs = NULL;
	new->next = NULL;
	new->struct_param_number = 0;
	return (new);
}

t_struct	*add_struct(t_struct *head, char *struct_name)
{
	t_struct	*trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_struct(struct_name);
	return (trav);
}

t_struct 	*push_struct(t_struct *head, char *struct_name)
{
	t_struct	*trav;

	trav = head;
	if (trav == NULL)
		trav = new_struct(struct_name);
	else
	{
		trav = add_struct(head, struct_name);
		trav = head;
	}
	return (trav);
}


t_struct	*add_struct_variable(t_struct *all_structs, char *struct_name,  t_fvars *parameters)
{
	t_struct	 *trav;

	trav = all_structs;
	while (trav)
	{
		if (strcmp(trav->struct_name, struct_name) == 0)
			break;
		trav = trav->next;
	}	
	trav->variables = add_to_param_list(
		trav->variables,
		parameters,
		trav->struct_param_number	
	);
	trav->struct_param_number++;	
	return (all_structs);
}

bool	verify_struct(char *struct_type, char *var_name)
{
	if (!does_variable_type_match(struct_type, var_name))
		return (false);
	return (true);
}

void	print_structs(t_struct *all_struct)
{
	t_struct	*trav;
	t_fvars		**param;
	trav = all_struct;
	while (trav)
	{
		int i = 0;
		printf("struct name : %s\n", trav->struct_name);
		param = trav->variables;
		while (i < trav->struct_param_number)
		{
			printf("var name %s\n", param[i]->name);
			printf("var type %s\n", param[i]->type);
			printf("var depth %d\n", param[i]->depth);
			i++;
		}
		trav = trav->next;
	}
}


bool		assert_struct_token(t_token *token, char *sname, char *vname)
{
	token = token->next;
	if (strcmp(token->type, "ID") == 0 && verify_struct(sname, vname) == false)
		return (false);
	return (true);		
}


void		create_struct_variable(char *struct_name, char *name, int depth, char *var_name)
{
	char *token;
	char *temp;
	char *var;

	temp = join(name, "->");
	var = join(temp, var_name);
	insert_into_db(struct_name, var, NULL, depth);
	free(temp);
	free(var);
}

bool		insert_struct_into_db(char *struct_name, char *name, int depth)
{
	extern t_struct *all_structs;
	t_struct *trav;
	t_fvars **variables;
	int i;
	char **sname;

	sname = split(struct_name, ' ');
	trav = all_structs;
	while (trav)
	{
		if (strcmp(trav->struct_name, sname[1]) == 0)
		{	
			variables = trav->variables;
			int i = 0;
			while (i < trav->struct_param_number)
			{
				create_struct_variable(struct_name, name, depth, variables[i]->name);
				i++;
			}
		}
		trav = trav->next;
	}
	return (false);
}
t_token		*struct_loop(t_token *token);

t_token		*handle_nested_struct(t_token *token, char *struct_name)
{
	t_token *trav;
	t_token	*head;
	char *datatype_name;
	t_temp_var *temp;
	t_token *print;
	t_temp_var *tvar;
	t_fvars *parameter;
	extern t_struct *all_structs;

	trav = token;
	print = trav;
	head = NULL;
	while (trav && strcmp(trav->name, ";") != 0 && strcmp(trav->name, "{") != 0)
	{
		head = push_token(head, trav->name, trav->type, 0,"NONE");
		trav = trav->next;
	}
	printf("\n");	
	if (strcmp(trav->name, ";") == 0)
	{
		temp = create_temp_var(head);
	}
	else if (strcmp(trav->name, "{") == 0)
	{
		trav = struct_loop(print);
		print->next->next = trav;
		tvar = create_temp_var(print);
		trav = tvar->curr;
		parameter = create_new_parameter(tvar->name, tvar->type, tvar->depth);
                all_structs = add_struct_variable(all_structs, struct_name, parameter);
                param_free(parameter);
		//trav = trav->next;
	}	
	return trav;
}

t_token		*struct_loop(t_token *token)
{
	t_token		*trav;
	int		brackets;
	t_temp_var	*temp_var;
	bool		first_bracket_found;
	extern char 	**start;
	char		*struct_name;
	t_fvars		*parameter;
	extern t_struct	*all_structs;
	char		*datatype_name;
	t_token		*prev;

	trav = token;
	datatype_name = join_with_space(token->name, token->next->name);
	if (value_found(datatype_name, start))
	{
		char *type;
		char *name;
		int depth;
		depth = 0;
		trav = trav->next->next;
		type = strdup(datatype_name);
		while (strcmp(trav->name, "*") == 0)
		{
			depth++;
			trav = trav->next;
		}
		if (strcmp(trav->type, "ID") == 0)
		{
			name = strdup(trav->name);
			trav = trav->next;
		}
		else
			return (false);
		
		if (strcmp(trav->name, "=") == 0)
			assert_struct_token(trav, type, trav->next->name);
		else if (strcmp(trav->name, ";") == 0)
		{
			insert_struct_into_db(datatype_name, name, depth);
			insert_into_db(datatype_name, name, "STRUCT", depth);
		}
		return (trav);
	}
	start = arraypush(start, datatype_name);	
	trav = trav->next;
	first_bracket_found = false;
	brackets = 0;
	while (trav)
	{	
		if (first_bracket_found == true && brackets == 0) break;
		else if (strcmp(trav->type, "ID") == 0 && first_bracket_found == false) 
		{
			struct_name = strdup(trav->name);
			all_structs = push_struct(all_structs, struct_name);
		}	
		else if (first_bracket_found == true && value_found(trav->name, start) == true)
		{
		
			if (strcmp(trav->name, "struct") == 0) 
			{
				trav = handle_nested_struct(trav, struct_name);
			}
			else 
			{
				temp_var = create_temp_var(trav);
				parameter = create_new_parameter(temp_var->name, temp_var->type, temp_var->depth);
				all_structs = add_struct_variable(all_structs, struct_name, parameter);
				param_free(parameter);				 
				trav = temp_var->curr; 
			}
		}	
		else if (strcmp(trav->name, "{") == 0)
		{
			if (first_bracket_found == false)
				first_bracket_found = true;
			brackets++;
		}
		else if (strcmp(trav->name, "}") == 0)
		{
			brackets--;
			trav = trav->next;
			if (brackets == 0 && first_bracket_found == true)
				break; 
		}
		else
			break;
		prev = trav;
		trav = trav->next;
	}
	free(datatype_name);
	return (trav);
}

bool		handle_struct_dereferencing(t_token *token)
{
	t_token	*trav;
	extern t_struct *all_structs;
	t_struct *trav_struct;
	t_db *object;
	int counter;
	char **segments;

	counter = 0;
	object = get_object_from_db(token->name);
	if (!object)
	{
		error_mode(token, "variable doesnt exist");
		return (false);
	}
	trav = token;
	trav_struct = all_structs;
	segments = split(object->type, ' ');
	while (trav_struct)
	{
		if (strcmp(trav_struct->struct_name, segments[1]) == 0)
		{
			trav = trav->next->next;
			counter = 0;
			while (counter < trav_struct->struct_param_number)
			{
				if (strcmp(trav_struct->variables[counter]->name, trav->name) == 0)
				{
					/*printf("found %s\n", trav->name);
					printf("variable datatype %s", trav_struct->variables[counter]->type);
					printf("variable depth %d\n", trav_struct->variables[counter]->depth);
					*/
					return (true);
				}
				counter++;
			}
			break;
		}
//		printf("trav struct name %s\n", trav_struct->struct_name);
		trav_struct = trav_struct->next;
	}
	return (false);
}


