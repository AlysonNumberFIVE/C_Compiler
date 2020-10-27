
#include "../inc/compiler.h"
#include <math.h>

char	**delete_segment(char **array, int start, int end)
{
	char **newarray;
	int i;
	
	i = 0;
	newarray = NULL;
	while (array[i])
	{
		if (i < start && i > end)
		{
			i++;
			continue;
		}
		newarray = arraypush(newarray, array[i]);
		i++;
	}
	return (newarray);
}

bool	arrchr(char **value, char *v)
{
	int i;

	i = 0;
	while (value[i]) 
	{
		if (strcmp(value[i], v) == 0)
			return (true);
		i++;
	}
	return (false);
}
char 	**segment_string(char **component, int start, int end);
void	print_array(char **array);
char	**remerge(char **first, char *in_between, char **second)
{
	char **new_merge;
	int i;

	new_merge = NULL;
	
	i = 0;
	if (first)
	while (first[i])
	{
		new_merge = arraypush(new_merge, first[i]);
		i++;
	}
	new_merge = arraypush(new_merge, in_between);
	i = 0;
	if (second)
	while (second[i])
	{
		new_merge = arraypush(new_merge, second[i]);
		i++;
	}
	return (new_merge);
}

char 	*mathematics(char **equation)
{
	int total;
	double value;
	char **first_half;
	char **second_half;

	total = 0;
	print_array(equation);
	while (arrchr(equation, "^") == true)
	{
		int index = 0;
		while (equation[index + 2]) 
		{
			if (strcmp(equation[index + 1], "^") == 0)
			{
				value = pow((double)atoi(equation[index]), (double)atoi(equation[index + 2]));
				first_half = segment_string(equation, 0, index);
				second_half = segment_string(equation, index + 3, arraylen(equation));
				// add free here
				equation = remerge(first_half, itoa(value), second_half);
				total = value;
				break;
			}
			index++;
		}
	}
	while (arrchr(equation, "/") == true || arrchr(equation, "*") == true)
	{
		int index = 0;
		while (equation[index + 2])
		{
			if (strcmp(equation[index + 1], "/") == 0 || strcmp(equation[index + 1], "*") == 0)
			{
				if (strcmp(equation[index + 1], "/") == 0)
					value = atoi(equation[index]) / atoi(equation[index + 2]);
				else
					value = atoi(equation[index]) * atoi(equation[index + 2]);
				first_half = segment_string(equation, 0, index);
				second_half = segment_string(equation, index + 3, arraylen(equation));
				// add another free here
				equation = remerge(first_half, itoa(value), second_half);
				total = value;
				break;
			}
			printf("here\n");
			index++;
		}
		printf("here\n");
	}
	while (arrchr(equation, "+") == true || arrchr(equation, "-") == true)
	{
		int index = 0;
		while (equation[index + 2])
		{
			if (strcmp(equation[index + 1], "+") == 0 || strcmp(equation[index + 1], "-") == 0)
			{
				if (strcmp(equation[index + 1], "+") == 0)
					value = atoi(equation[index]) + atoi(equation[index + 2]);
				else
					value = atoi(equation[index]) - atoi(equation[index + 2]);
				first_half = segment_string(equation, 0, index);
				second_half = segment_string(equation, index + 3, arraylen(equation));
				equation = remerge(first_half, itoa(value), second_half);
				printf("here\n");
				print_array(equation);
				total = value;
				break;
			}
			index++;
		}	
	}
	return (strdup(itoa(total)));
}


char	**segment_string(char **components, int start_index, int end_index)
{
	char **sub_array;
	int counter;	

	sub_array = NULL;
	counter = start_index;
	while (start_index < end_index)
	{
		sub_array = arraypush(sub_array, components[start_index]);
		start_index++;
	}
	return (sub_array);
}

void	print_array(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		printf("%s ", str[i]);
		i++;
	}
}

char	*determine_sum(char **components)
{
	//extern t_db *list;
 	//extern int max_number;
	//char **components;
	int counter;	
	
	int start_index = -1;
	int end_index = -1;
	int brackets = 0;
	char **first_half = NULL;
	char **second_half = NULL;
	char **equation;
	char *total;
	
	//components = split(possible_string, ' ');
	equation = components;
	print_array(components);
	counter = 0;
	while (components[counter])
	{
		if (strcmp(components[counter], "(") == 0)
		{
			brackets = 1;
			start_index = counter;
		}
		else if (strcmp(components[counter], ")") == 0)
		{
			brackets--;
			end_index = counter;
			if (brackets == 0)
			{
				first_half = segment_string(components, 0, start_index);
				second_half = segment_string(components, end_index + 1, arraylen(components));
				equation = segment_string(components, start_index + 1, end_index);
				break ;
			}
		}
		counter++;
	}
	total = mathematics(equation);
	if (first_half || second_half)
	{
		equation = remerge(first_half, total, second_half);	
		return (determine_sum(equation));
	}
	return (total);
}

bool	is_valid_equation(char **equation)
{
	extern int max_number;
//	extern t_db **list;
	int counter;
	bool symbol;	
//	char *db_value;
	int brackets;

	symbol = false;
	counter = 0;
	while (equation[counter])
	{
		if (strcmp(equation[counter], "(") == 0)
		{
			brackets++;
		}
		else if (strcmp(equation[counter], ")") == 0)
		{
			brackets--;
		}
		else if (symbol == false)
		{
			/*if (!atoi(equation[counter]))
			{
				db_value = get_from_db(equation[counter]);
				if (db_value == NULL)
					printf("Error found at this fucking pooint\n");
				else 
				{
					free(equation[counter]);
					equation[counter] = strdup(db_value);
					free(db_value);
				}
			}*/
			symbol = true;
		}
		else if (symbol == true)
		{
			printf("equation is %s\n", equation[counter]);
			if (strlen(equation[counter]) == 1 && strchr("+-/*^><|", equation[counter][0]))
				symbol = false;
			else
				printf("a new error is found\n");
		}
		if (brackets < 0)
		{
			printf("error in brackets\n");
		}
		counter++;
	}
	printf("symbol is %d\n", symbol);
	return (symbol);
}


int	main(void)
{
	char *sum = "1 + 2 * ( 42 / 2 ) * 11";
	sum = "1 + ( 162 + 1 * 2 * ( 11 * 2 ) + 4 + 5 ) / 2 + 3";
//	sum = "1 + 1";
	char **pieces = split(sum, ' ');
	is_valid_equation(pieces);
//	determine_sum(pieces);
	return (0);
}


