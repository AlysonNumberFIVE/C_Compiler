
#include <ctype.h>
#include "../inc/compiler.h"
#define FIRST_ORDER_LENGTH 4
#define PRIMITIVES_LENGTH 12
#define RESERVED_LENGTH 33
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



char	*value_checker(char **components)
{
	int 	counter;
	char 	*array_value;	
	bool	comma_flag;

	counter = 0;
	if ((components[0][0] == '\"' || components[0][0] == '\'') && 
		arraylen(components) == 2 &&
		strcmp(components[1], ";") == 0)
		return (strdup(components[0]));

	if (atoi(components[0]) && arraylen(components) == 2 &&
		strcmp(components[1], ";") == 0)
		return (strdup(components[0]));
	
	if (validate_id(components[0]))
		printf("check that ID exists in variable table\n");
		
	// handling those shit arrays.
	if (strcmp(components[0], "{") == 0)
		counter++;
	array_value = strdup("{");
	comma_flag = false;
	while (components[counter] && strcmp(components[counter], ";") != 0)
	{
		if (strcmp(components[counter], "{") == 0)
		{
			array_value = join_with_space(array_value, components[counter]);
			comma_flag = false;
		}
		else if (strcmp(components[counter], "}") == 0)
		{
			array_value = join_with_space(array_value, components[counter]);
			comma_flag = true;
		}
		else if (comma_flag == false && (components[counter][0] == '\"' ||
			components[counter][0] == '\'' ||
			atoi(components[counter]))) // ||
			// verify existence of variable if exists
		{
			printf("here we are\n");	
			array_value = join_with_space(array_value, components[counter]);
			comma_flag = true;
			printf("afterwards\n");
		}
		else if (comma_flag == true && (strcmp(components[counter], ",") == 0))
		{
			array_value = join_with_space(array_value, components[counter]);
			comma_flag = false;
		}
		else
			printf("Error : incorrect variable blah blah\n");
		counter++;
	}
	if (strcmp(components[counter], ";") != 0 || arraylen(components) - 1 != counter)
		printf("error in length of line\n");
	return (array_value);		
}


bool	validate_variable(char **components)
{
	int	counter;
	int 	depth;	
	char 	*datatype;
	char 	*variable_name;
	char	**sub_sequence;
	bool	assignment;
	
	assignment = false;
	depth = 0;
	datatype = NULL;
	sub_sequence = NULL;
	counter = 0;
	while (components[counter])
	{
		if (array_search(reserved, RESERVED_LENGTH, components[counter]))
			datatype = is_datatype(datatype, components[counter]);
	
		else if (strcmp(components[counter], "*") == 0)
			depth++;
			
		else if (datatype && validate_id(components[counter]))
			variable_name = strdup(components[counter]);
	
		else if (strcmp(components[counter], "=") == 0)
		{
			assignment = true;
			break;
		}
		else if (strcmp(components[counter], ";") == 0)
			break;
		counter++;
	}
	counter++;
	printf("datatype is %s\n", datatype);
	printf("variable name %s\n", variable_name);
	printf("depth is %d\n", depth);
	if (assignment == true)
	{
		printf("%s\n", value_checker(&components[counter]));
	}
/*
	if (assignment == true)
	{
		
	}
*/

}

/*
int	main(void)
{
	char *variable = "unsigned long * str = { \'c\' , \'a\' , \'t\' } ;";	
	variable = "char *str = { { 4 } , { 4 } , { 4 } } ;";
	char **pieces = split(variable, ' ');
		
	validate_variable(pieces);
	return (0);
}

*/









