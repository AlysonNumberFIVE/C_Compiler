

#include "../inc/compiler.h"

typedef struct s_struct
{
	char *struct_name;
	int struct_param_number;
	t_favs	*variables;	
}	t_struct;

t_struct	*new_struct(char *struct_name)
{
	t_struct	*new;

	new = (t_struct *)malloc(sizeof(t_struct));
	new->struct_name = strdup(struct_name);
	new->next = NULL;
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

	trav = head;
	while (trav)
	{
		if (strcmp(trav->struct_name, struct_name) == 0)
			break;
		trav = trav->next;
	
	trav->parameters = add_to_param_list(
		this->parameters,
		parameters,
		this->struct_param_numbers	
	);
	trav->struct_param_number++;	
	return (all_struct);
}


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



t_struct	*create_struct(t_token *tokens)
{
	t_token	*trav;
	char *struct_name;

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
		
	
}
















