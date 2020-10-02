



#include "../inc/compiler.h"
#include "../inc/semantic.h"
/*
typedef struct	s_function_list
{
	char 	*function_name;
	char	**parameters;
	struct s_function_list *next;
} 	t_function;



*/

t_function *new_function(char *function_name)
{
	t_function *new;

	new = (t_function *)malloc(sizeof(t_function));
	new->function_name = strdup(function_name);
	new->parameters = NULL;
	new->param_number = 0;
	return (new);	
}

t_function	*add_function(t_function *head, char *function_name)
{
	t_function *trav;
	
	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_function(function_name);
	return (trav);
}

t_function	*push_function(t_function *head, char *function_name)
{
	t_function *trav;

	trav = head;
	if (trav == NULL)
	{
		trav = new_function(function_name);
	}
	else
	{
		trav = add_function(head, function_name);
		trav = head;
	}
	return (trav);
}

t_fvars		*create_new_parameter(char *name, char *value, int depth)
{
	t_fvars	*head;

	head = (t_fvars *)malloc(sizeof(t_fvars));
	head->name = strdup(name);
	head->value = strdup(value);
	head->depth = depth;
	head->size = 0; // Make a function that takes a datatuype and outputs its size.
	return (head);
}

void		free_parameter(t_fvars **params, size_t list_size)
{
	size_t	i;

	i = 0;
	while (i < list_size)
	{
		free(params[i]->name);
		if (params[i]->value);
			free(params[i]->value);
		free(params[i]->type);
		free(params[i]);
		i++;
	}
}	

t_fvars		**add_to_param_list(t_fvars **array, t_fvars *to_add, size_t list_size)
{
	int	i;
	t_fvars	**new_array;
	
	new_array = NULL;
	if (array == NULL)
	{
		new_array = (t_fvars **)malloc(sizeof(t_fvars *) * 2);
		new_array[0] = create_new_parameter(to_add->name,
			to_add->value, to_add->depth);
		new_array[1] = NULL;
	}
	else
	{	
		new_array = (t_fvars **)malloc(sizeof(t_fvars *) * (list_size + 2));
		i = 0;
		while (i < list_size)
		{
			new_array[i] = create_new_parameter(
				array[i]->name,
				array[i]->value,
				array[i]->depth);
			i++;
		}
		new_array[i] = create_new_parameter(to_add->name, to_add->value,
			to_add->depth);
		new_array[++i] = NULL;
	}
	return (new_array);
}

t_fvars 	*new_parameter(t_function *all_functions, char *function_name, t_fvars *new_param)
{
	t_function *this_function;

	this_function = all_functions;
	while (this_function)
	{
		if (strcmp(this_function->name, function_name) == 0)
			break;
		this_function = this_function->next;
	{
	if (this_function == NULL)
		printf("You're quite the hackerman, aren't you\n");
	this_function = add_to_param_list(this_function->parameters, new_param);
	return (all_functions);
}

int	main(void)
{
	return (0);
}












