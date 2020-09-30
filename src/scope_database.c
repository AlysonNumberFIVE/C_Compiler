

#include "../inc/compiler.h"

int max_number = 0;

typedef struct 	s_scope_database
{
	char	*type;
	char 	*name;
	char	*value;
	struct s_scope_database *next;
}	t_db;

t_db 	**list = NULL;

t_db	*new_object(char *type, char *name, char *val)
{
	t_db	*new;

	new = (t_db *)malloc(sizeof(t_db));
	new->type = strdup(type);
	new->name = strdup(name);
	new->value = strdup(val);
	new->next = NULL;
	return (new); 
}

t_db	*add_object(t_db *db, char *type, char *name, char *val)
{
	t_db	*add;

	add = db;
	while (add->next)
		add = add->next;
	add->next = new_object(type, name, val);
	return (add);
}

t_db	*push_object(t_db *db, char *type, char *name, char *val)
{
	t_db	*new;

	new = db;
	if (new == NULL)
	{
		new = new_object(type, name, val);
	}
	else
	{
		new = add_object(db, type, name, val);
		new = db;
	}
	return (new);
}

void	free_db(t_db *db)
{
	t_db *trav;

	while (db != NULL)
	{
		trav = db;
		db = db->next;
		free(trav->type);
		free(trav->name);
		free(trav->value);
		free(trav);
	}
}

void	insert_into_db(char *type, char *name, char *val)
{
	t_db	*object;

	if (list == NULL)
	{
		list = (t_db **)malloc(sizeof(t_db *) * 500);
		bzero(list, sizeof(t_db) * 500);
		list[0] = push_object(list[0], type, name, val);
	}
	else 	
	{	
		list[max_number] = push_object(list[max_number], type, name, val);
	}

}

char	*get_from_db(char *variable)
{
	t_db	*scan;
	int	traverse_table;
	traverse_table = max_number;
	while (traverse_table > -1)
	{
		scan = list[traverse_table];
		while (scan)
		{
			if (strcmp(variable, scan->name) == 0)
				return (strdup(scan->value));
			scan = scan->next;
		}
		traverse_table--;
	}	 
	return (NULL);
}

void	drop_last_table(void)
{
	free(list[max_number]);
	list[max_number] = NULL;
	max_number--;
}

void	add_new_table(void)
{
	max_number++;
}

int	main(void)
{
	return (0);
}



