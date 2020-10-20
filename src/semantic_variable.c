

#include <ctype.h>
#include "../inc/token.h"
#include "../inc/semantic.h"
#include "../inc/database.h"
#include "../inc/compiler.h"
#define FIRST_ORDER_LENGTH 4
#define PRIMITIVES_LENGTH 12
#define RESERVED_LENGTH 33
#define ARR 7
/*
static char reserved[33][9] = {
    "auto\0",     "break\0",    "case\0",     "char\0",
    "const\0",    "continue\0", "default\0",  "do\0",
    "int\0",      "long\0",     "register\0", "return\0",
    "short\0",    "signed\0",   "sizeof\0",   "static\0",
    "struct\0",   "switch\0",   "typedef\0",  "union\0",
    "unsigned\0", "void\0",     "volatile\0", "while\0",
    "double\0",   "else\0",     "enum\0",     "extern\0",
    "float\0",     "for\0",     "gaoto\0",     "if\0",
    "size_t\0"
}; */

static char first_order[4][9] = {
    "unsigned\0",
    "static\0",
    "extern\0",
    "typedef\0"
};

static char primitives[38][9] = {
    "char\0",
    "const\0",
    "void\0",
    "struct\0",
    "int\0",
    "short\0",
    "double\0",
    "float\0",
    "size_t\0",
    "long\0",
    "signed\0",
    "void\0",
};

char	*join_with_space(char *first, char *second)
{
	char *temp;
	char *new;

	new = join(first, " ");
	temp = join(new, second);
	free(new);
	return (temp);
}

bool	array_search(char array[][9], int size, char *to_find)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (strcmp(array[i], to_find) == 0)
			return (true);
		i++;
	}
	return (false);
}

char	*is_datatype(char *datatype, char *to_add)
{
	if (datatype)
	{
		bool in_first_order;
		bool is_primitive;
		char *new_datatype;

		is_primitive = false;
		in_first_order = false;
		in_first_order = array_search(first_order, FIRST_ORDER_LENGTH, datatype);
		if (in_first_order == false)
		{
			
			printf("invalid variable typing\n");
			free(datatype);
			return (NULL);
		}
		is_primitive = array_search(primitives, PRIMITIVES_LENGTH, to_add);
		if (in_first_order && is_primitive)
		{
			new_datatype = join_with_space(datatype, to_add);
			free(datatype);
			return (new_datatype);
		}
		free(datatype);
		return (NULL);
	}
	if (array_search(first_order, FIRST_ORDER_LENGTH, to_add) ||
		array_search(primitives, PRIMITIVES_LENGTH, to_add))
		datatype = strdup(to_add);
	return (datatype);
}

bool	validate_id(char *str)
{
	if (str[0] == '_' || isalpha(str[0]) && !array_search(reserved, RESERVED_LENGTH, str))
		return (true);
	return (false);
}

char	*value_checker(t_token *components)
{
	int 	counter;
	char 	*array_value;	
	bool	comma_flag;
	t_db	*object;
	t_function *function;
	char	*db_checker;
	t_function *this_function;
	int	comma_count;
	extern t_stack *stack;
	t_token *error;	

	comma_count = 0;
	counter = 0;
	if (strcmp(components->type, "LITERAL") == 0 &&
		strcmp(components->next->name, ";") == 0)
		return (strdup(components->name));

	if (strcmp(components->type, "NUM") == 0 &&
		strcmp(components->next->name, ";") == 0)
		return (strdup(components->name));
	
	if (strcmp(components->type, "ID") == 0 || 
		(strcmp(components->name, "&") == 0 && 
		strcmp(components->next->type, "ID") == 0))
	{
		if (is_valid_equation(components, ";"))
		{
			return (strdup("VALID"));
		}
		else
		{
			error_mode(components, "Variable does not exist");
			return (NULL);
		}
		/*
		db_checker = get_from_db(components->next->name);
		if (!db_checker)
		{
			error_mode(components, "Error : varaible does not exist");
			// printf("Error : variable does not exist\n");
			return (NULL);
		}
		return (strdup(db_checker));*/
	}
	if (validate_id(components->name))
	{
		db_checker = get_from_db(components->name);
		if (!db_checker)
		{
			printf("error : variable does not exist\n"); 
			return (NULL);
		}
		return (strdup(db_checker));
	}	
	// handling those shit arrays.
	if (strcmp(components->name, "{") == 0)
	{
		stack = push_stack(stack, ARR);
		comma_count++;
		components = components->next;
		array_value = strdup("{");
		comma_flag = false;
		while (components && strcmp(components->name, ";") != 0)
		{
			if (strcmp(components->name, "{") == 0)
			{
				comma_count++;
				comma_flag = false;
			}
			else if (strcmp(components->name, "}") == 0)
			{
				comma_count--;
				comma_flag = true;
			}
			else if (comma_flag == false) // ||
				// verify existence of variable if exists
			{
				if (!is_valid_equation(components, ","))
				{
					printf("error: invalid assignment of arrays\n");
					return (NULL);	
				}
				comma_flag = true;
			}
			else if (comma_flag == true && components && (strcmp(components->name, ",") == 0))
			{
				comma_flag = false;
			}
			else
				printf("Error : incorrect variable blah blah\n");	
		components = components->next;
		}
	}
	else if (is_valid_equation(components, ";"))
	{
		return strdup("AVLID");
	}
	/*(if (strcmp(components->name, ";") != 0)
	{
		error = NULL;
		printf("components is %s\n", components->name);
		components = error_recover(components, "Error : missing semicolon\n",
			push_token(error, ";", "SEMICOLON", 0, "NULL"));
		
	}
	if (is_valid_equation(components, ";"))
	{
		return strdup("AVLID ");
	} */
	if (strcmp(components->name, ";") != 0)
		printf("error in length of line\n");
	array_value = strdup("VALID ARRAY\n");
	stack = pop_stack(stack);
	return (array_value);		
}







