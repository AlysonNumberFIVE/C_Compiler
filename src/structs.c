
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

/*
typedef struct s_variable_block
{
	char *name;
	char *type;
	t_token *curr;
	int depth;
}	t_temp_var;

t_temp_var	*create_temp_var(t_token *token)
{
        int             depth;
        extern int      max_number;
        extern t_db     *list;
        t_hashtable     *variables;
	t_temp_var	*temp;

	temp = (t_temp_var *)malloc(sizeof(t_temp_var));
        temp->depth = 0;
	trav = token;
        if (value_found(trav->name, start) == true)
        {
                temp->type = strdup(trav->name);
                trav = trav->next;
        }
        else
                return (false);

        while (strcmp(trav->name, "*") == 0)
        {
                temp->depth++;
                trav = trav->next;
        }
        if (strcmp(trav->type, "ID") == 0)
        {
                temp->name = strdup(trav->name);
                trav = trav->next;
        }
        else
                return (false);
	temp->curr = trav;
	return (temp);
}
*/

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

	first_bracket_found = false;
	brackets = 0;
	trav = token->next;
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
				trav = struct_loop(trav);
			else 
			{
				temp_var = create_temp_var(trav);
				parameter = create_new_parameter(temp_var->name, temp_var->type,
					temp_var->depth);
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
		else break;
		trav = trav->next;
	}
	if (brackets == 0)
		printf("pass\n");
	else
		printf("falied\n");
	print_structs(all_structs);
	return (trav);
}
/*
t_struct	*create_struct(t_token *tokens)
{
	t_token		*trav;
	char		*struct_name;
	t_temp_vars	*temp;

	trav = tokens->next;
	if (strcmp(trav->type, "ID") == 0)
	{
		struct_name = strdup(trav->name);
		trav = trav->next;
	}
	else
		return (false);
	if (strcmp(trav->name, "{") == 0)
		trav = trav->next;
	while (trav && strcmp(trav->name, ";") != 0)
	{
		temp_vars = create_temp_vars(trav);
		trav = trav->next;
		if (ttemp_vars->name == NULL) 
		{
			trav = temp_vars->cuurr;
			break ;
		}
		trav = trav->next;
	}
	if (strcmp(trav->	
}

*/














