


#include "../inc/parser.h"
#define C_SIZE 29
char 	c_datatypes[30][30] = {
	"char\0",
	"signed char\0",
	"unsigned char\0",
	"short\0",
	"short int\0",
	"signed short\0",
	"signed short int\0",
	"unsigned short\0",
	"unsigned short int\0",
	"int\0",
	"signed\0",
	"signed int\0",
	"unsigned\0",
	"unsigned int\0",
	"long \0",
	"long int\0",
	"signed long\0",
	"signed long int\0",
	"unsigned long\0",
	"unsigned long int\0",
	"long long\0",
	"long long int\0",
	"signed long long\0",
	"signed long long int\0",
	"unsigned long long\0",
	"unsigned long long int\0",
	"float\0",
	"double\0",
	"long double\0"
};

typedef struct	s_temp_data
{
	char *name;
	struct s_temp_data *next;
}	t_temp;

static t_temp	*new_temp(char *name)
{
	t_temp	*new;

	new = (t_temp *)malloc(sizeof(t_temp));
	new->name = strdup(name);
	new->next = NULL;
	return (new);
}

static t_temp	*add_temp(t_temp *head, char *name)
{
	t_temp	*trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_temp(name);
	return (trav);
}

static t_temp	*push_temp(t_temp *head, char *name)
{
	t_temp	*trav;

	trav = head;
	if (trav == NULL)
	{
		trav = new_temp(name);
	}
	else
	{
		trav = add_temp(head, name);
		trav = head;
	}
	return (trav);
}

static t_temp	*delete_node(t_temp *head, char *name)
{
	t_temp	*trav;
	t_temp	*prev;

	trav = head;
	
	if (trav && strcmp(trav->name, name) == 0)
	{
		head = head->next;
		free(trav->name);
		free(trav);
		return (head);
	}
	
	else if (trav)
	{	
		while (trav->next)
		{
			if (strcmp(trav->next->name, name) == 0)
			{	
				prev = trav->next;
				trav->next = trav->next->next;
				free(prev->name);
				free(prev);
				return (head);
			}
			trav = trav->next;
		}
		if (trav && strcmp(trav->name, name) == 0)
		{
			free(trav->name);
			free(trav);
			return (NULL);
		}
	}
 
	return (head);
}

static bool	evaluate_datatype_line(char **against, t_pstack *to_check, int datatype_len)
{
	t_temp	*temp;
	t_temp	*second;
	int 	i;
	t_pstack *trav;
	int 	counter;
	t_temp	*temp_head;	
	t_temp	*second_head;
	
	counter = 0;
	temp = NULL;
	i = 0;
	trav = to_check;
	while (trav && counter < datatype_len)
	{
		temp = push_temp(temp, trav->token);
		trav = trav->prev;
		counter++;
	}
	temp_head = temp;
	
	second = NULL;
	i = 0;
	while (against[i])
	{
		second = push_temp(second, against[i]);
		i++;
	}
	second_head = second;
	while (second)
	{
		temp = temp_head;
		while (temp)
		{
			if (temp->name && second->name && strcmp(second->name, 
				temp->name) == 0)
			{
				free(temp->name);
				temp->name = NULL;
				free(second->name);
				second->name = NULL;
				break;
			}
			temp = temp->next;
		}
		second = second->next;
	}
	second = second_head;
	while (second)
	{
		if (second->name) return (false);
		second = second->next;
	}
	temp = temp_head;
	while (temp)
	{
		if (temp->name) return (false);
		temp = temp->next;
	}
	return (true);
}


bool	is_datatype_correct(t_pstack *stack, int datatype_len)
{
	t_pstack *trav;
	int i;
	char **clist;
	extern t_current_var	*current_variable;
	
	trav = stack;
	i = 0;
	while (i < C_SIZE)
	{
		clist = split(c_datatypes[i], ' ');
		if (evaluate_datatype_line(clist, stack, datatype_len) == true)
		{
			current_variable = push_curr_var(current_variable, c_datatypes[i]);
			free2d(clist);
			return (true);
		}
		free2d(clist);
		i++; 
	} 
	return (false);
}	















