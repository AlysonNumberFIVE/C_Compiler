



#include "../inc/compiler.h"


typedef struct	s_function_list
{
	char 	*function_name;
	char	**parameters;
	struct s_function_list *next;
} 	t_function;


t_function *new_function(char *function_name, char **parameters)
{
	t_function *new;

	new = (t_function *)malloc(sizeof(t_function));
	new->function_name = strdup(function_name);
	new->parameters = NULL;
	if (parameters)
		new->parameters = arraydup(parameters);
	return (parameters);	
}

t_function	*add_function(t_function *head, char *function_name, char **paramters)
{
	t_function *trav;
	
	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_function(function_name, parameters);
	return (trav);
}

t_function	push_function(t_function *head, char *function_name, char **parameters)
{
	t_function *trav;

	trav = head;
	if (trav == NULL)
	{
		trav = new_funciton(function_name, parameters);
	}
	else
	{
		trav = add_function(head, function_name, parameters);
		trav = head;
	}
	return (trav);
}
















