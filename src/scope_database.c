

#include "../inc/compiler.h"
#include "../inc/database.h"

int max_number = 0;
/*
typedef struct 	s_scope_database
{
	char	*type;
	char 	*name;
	int 	depth;
	int 	size;
	char	*value;
	struct s_scope_database *next;
}	t_db;
*/
t_db 	**list = NULL;

t_db	*new_object(char *type, char *name, char *val, int depth)
{
	t_db	*new;

	new = (t_db *)malloc(sizeof(t_db));
	new->type = strdup(type);
	new->name = strdup(name);
	new->value = strdup(val);
	new->depth = depth;
	new->next = NULL;
	return (new); 
}

t_db	*add_object(t_db *db, char *type, char *name, char *val, int depth)
{
	t_db	*add;

	add = db;
	while (add->next)
		add = add->next;
	add->next = new_object(type, name, val, depth);
	return (add);
}

t_db	*push_object(t_db *db, char *type, char *name, char *val, int depth)
{
	t_db	*new;

	new = db;
	if (new == NULL)
	{
		new = new_object(type, name, val, depth);
	}
	else
	{
		new = add_object(db, type, name, val, depth);
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

void	insert_into_db(char *type, char *name, char *val, int depth)
{
	t_db	*object;

	if (list == NULL)
	{
		list = (t_db **)malloc(sizeof(t_db *) * 500);
		bzero(list, sizeof(t_db *) * 500);
		list[0] = push_object(list[0], type, name, val, depth);
	}
	else 	
	{	
		list[max_number] = push_object(list[max_number], type, name, val, depth);
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

bool	does_variable_exist(char *variable)
{
	int current_number;
	t_db *object;

	current_number = max_number;
	while (current_number > -1)
	{
		object = list[current_number];
		while (object)
		{
			if (strcmp(object->name, variable) == 0)
				return (true);
			object = object->next;
		}
		current_number--;
	}
	return (false);
}

void	print_variables(void)
{
	int current;

	current = 0;
	while (current < max_number + 1)
	{
		t_db *object;
		object = list[current];
		if (object == NULL)
			printf("NONE\n");
		else
			while (object)
			{
				printf("%s ->", object->name);
				object = object->next;
			}
		printf("\n");
		current++;
	}
}
/*
int	main(void)
{

	insert_into_db("char", "str", "hello", 1);
	insert_into_db("int", "val", "42", 0);
	char *val = get_from_db("str");	
	add_new_table();
	insert_into_db("int", "load", "NULL", 0);
	insert_into_db("void", "value", "ptr", 1);
	add_new_table();
	print_variables();
	val = get_from_db("load");
	printf("val is %s\n", val);
	drop_last_table();
	drop_last_table();
	val = get_from_db("load");
	if (val)
		printf("failed\n");
	printf("%d\n", max_number);
	
	return (9);
}
*/




