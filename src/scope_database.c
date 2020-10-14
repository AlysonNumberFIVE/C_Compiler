
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
	if (val)
		new->value = strdup(val);
	else
		new->value = NULL;
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

bool	insert_into_db(char *type, char *name, char *val, int depth)
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
		t_db *object = list[max_number];
		while (object)
		{
			if (strcmp(name, object->name) == 0)
			{
				printf("error : variable %s already defined\n", name);
				return (false);	
			}
			object = object->next;
		}	
		list[max_number] = push_object(list[max_number], type, name, val, depth);
	}
	return (true);
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

t_db	*get_object_from_db(char *name)
{
	t_db 	*scan;
	int	traverse_table;
	
	traverse_table = max_number;
	while (traverse_table > -1)
	{
		scan = list[traverse_table];
		while (scan)
		{
			if (strcmp(name, scan->name) == 0)
				return (new_object(scan->type, scan->name, scan->value, scan->depth));
			scan = scan->next;
		}
		traverse_table--;
	}
	return (NULL);
}

void	drop_last_table(void)
{
	printf("max_number %d\n", max_number);
	free(list[max_number]);
	list[max_number] = NULL;
	max_number--;
}

void	add_new_table(void)
{
	max_number++;
}

bool	update_variable_value(char *variable, char *new_value)
{
	int current_number;
	t_db *object;

	if (list == NULL)
	{
		printf("error : variable doens't exist\n");
		return (false);
	}
	current_number = max_number;
	while (current_number > -1)
	{
		object = list[current_number];
		while (object) 
		{
			if (strcmp(object->name, variable) == 0)
			{
				if (object->value)
					free(object->value);
				object->value = strdup(new_value);
				return (true);
			}
			object = object->next;
		}
		current_number--;
	}
	printf("error : variable doesn't exist\n");
	return (false);
}

bool	does_variable_exist(char *variable)
{
	int current_number;
	t_db *object;

	if (!list)
		return (false);
	current_number = max_number;
	while (current_number > -1)
	{
		object = list[current_number];
		while (object)
		{
			printf("object is\n");
			printf("%s\n", object->name);
			if (strcmp(object->name, variable) == 0)
				return (true);
			object = object->next;
		}
		current_number--;
	}
	return (false);
}

bool	does_variable_type_match(char *datatype, char *variable)
{
	int current_number;
	t_db *object;

	current_number = max_number;
	while (current_number > -1)
	{
		object = list[current_number];
		while (object)
		{
			if (strcmp(object->name, variable) == 0 &&
				strcmp(object->type, datatype) == 0)
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
	
	if (list == NULL)
	{
		printf("No variables stored\n");
		return ;
	}
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
				printf("%s  %s ->", object->name, object->value);
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
	insert_into_db("int", "v2", "cheese", 2);
	add_new_table();
	print_variables();
	update_variable_value("str", "goodbye");
	val = get_from_db("load");
	printf("val is %s\n", val);
	val = get_from_db("load");
	if (!val)
		printf("failed\n");
	printf("%d\n", max_number);
	print_variables();
	return (9);
}

*/
