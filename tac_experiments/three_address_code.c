
#include "intermediate.h"
#include <stdbool.h>
#include <stdio.h>
#include "alylibc/inc/lib.h"

int 	number = 1;
int	line = 1;
int	label = 1;
t_code	*assembly = NULL;

char 	**extract(char **str, int from, int to)
{
	char **new;
	int distance;
	int counter;

	new = (char **)malloc(sizeof(char *) * (to - from + 1));
	distance = to - from;
	counter = 0;
	while (counter < distance)
	{
		new[counter] = strdup(str[counter]);
		counter++;
	}
	new[counter] = NULL;
	return (new);
}

char 	**insertion(char **first_half, char *piece, char **second_half)
{
	char **new;
	size_t size;
	int counter;
	int i;

	size = arraylen(first_half) + arraylen(second_half) + 2;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	counter = 0;
	i = 0;
	while (first_half[counter])
	{
		new[i] = strdup(first_half[counter]);
		counter++;
		i++;	
	}
	new[i++] = strdup(piece);
	counter = 0;
	while (second_half[counter])
	{
		new[i] = strdup(second_half[counter]);
		i++;
		counter++;
	}
	new[i] = NULL;
	return (new);
}

bool	in(char **str, char *c)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (strcmp(str[i], c) == 0)
			return (true);
		i++;
	}
	return (false);
}

char	*address_line(char *op1, char *sym, char *op2)
{
	char *buffer;

	buffer = (char *)malloc(4096);
	bzero(buffer, 4096);
	snprintf(buffer, 4096, "t%d = %s  %s  %s", line, op1, sym, op2);
//	printf("t%d = %s  %s  %s\n", line, op1, sym, op2);
	assembly = push_line(assembly, number, buffer);
	number++; 
}

void	print_list(char **str)
{
	int i;

	printf("print_list\n");
	i = 0;
	while (str[i])
	{
		printf(" %s ", str[i]);

	}
	printf("\n");
}

char 	**print_address_line(char **equation, int counter)
{
	char *t;
	char **first_half;
	char **second_half;

	address_line(equation[counter], equation[counter + 1], equation[counter + 2]);
	t = join("t", itoa(line));
	line++;
	first_half = extract(equation, 0, counter);
	second_half = extract(&equation[counter + 3], counter, arraylen(equation) - 3);
	equation = insertion(first_half, t, second_half);
	return (equation);
}

char 	*mathematics(char **equation)
{
	int counter;
	int index;
	int value;
	int total;
	char **first_half;
	char **second_half;
	char *t;
	
	
	counter = 0;
	while (in(equation, "*") == true || in(equation, "/") == true)
	{
		counter = 0;
		while (equation[counter + 2])
		{
			if (strcmp(equation[counter + 1], "/") == 0 || strcmp(equation[counter + 1], "*") == 0)
			{
				equation = print_address_line(equation, counter);
				break;
			}
			counter++;
		}		
	}
	counter = 0;
	while (in(equation, "+") == true || in(equation, "-") == true)
	{
		counter = 0;
		while (equation[counter + 2])
		{
			if (strcmp(equation[counter + 1], "+") == 0 || strcmp(equation[counter + 1], "-") == 0)
			{
				equation = print_address_line(equation, counter);
				break;
			}
			counter++;
		}
	}
	while (in(equation, ">") == true || in(equation, "<") == true ||
		in(equation, "==") == true || in(equation, "!=") == true)
	{
		counter = 0;
		while (equation[counter + 2])
		{
			if (strcmp(equation[counter + 1], ">") == 0 || strcmp(equation[counter + 1], "<") == 0 ||
				strcmp(equation[counter + 1], "==") == 0 ||
				strcmp(equation[counter + 1], "!=") == 0)
			{
				equation = print_address_line(equation, counter);
				break;
			}
			counter++;
		}
	}
	t = join("t", itoa(line - 1));
	return (t);
}

bool	three_address_code(char **str)
{
	int start_index = -1;
	int end_index = -1;
	char **first_half = NULL;
	char **second_half = NULL;
	char **equation;
	int counter = 0;
	int brackets = 0;
	char *ret;

	equation = str;
	while (str[counter])
	{
		if (strcmp(str[counter], "(") == 0)
		{
			brackets = 1;
			start_index = counter;	
		}
		else if (strcmp(str[counter], ")") == 0)
		{
			brackets -= 1;
			end_index = counter;
			if (brackets == 0)
			{
				first_half = extract(str, 0, start_index);
				second_half = extract(&str[end_index + 1], end_index, arraylen(str) - 1);
				equation = extract(&str[start_index + 1], start_index, end_index - 1);
				break;
			}
		}
		counter++;
	}
	ret = mathematics(equation);
	if (first_half || second_half)
	{
		equation = insertion(first_half, ret, second_half);
	 	return (three_address_code(equation));
	}		
	return (true);
	
}

bool	handle_while_generation(char **str)
{
	char *l;
	if (strcmp(str[0], "while") == 0)
	{
		l = join("L", itoa(label));
		assembly = push_line(assembly, label, l);
		label++; 
	}
}

void 	print_asm(t_code *asesmbly)
{
	t_code 	*trav;

	trav = assembly;
	while (trav)
	{
		printf("%d : %s\n", trav->line_number, trav->line);
		trav = trav->next;
	}	
}

bool	tac_conditions(char **str)
{
	int counter;
	char *block;

	block = strdup(str[0]);
		
}

t_code	*edit_last_line(t_code *assembly)
{
	t_code *trav;
	char *new_line;
	char **segments;

	trav = assembly;
	while (trav->next)
		trav = trav->next;
	segments = split(trav->line, '=');
	new_line = join("if ", segments[1]);
	free(trav->line);
	trav->line = strdup(new_line);
	return (assembly);	
}

bool	tac_conditional(t_code *assembly, int condition)
{
	if (condition == 1)
	{

	}
}

int main(void)
{
	char **equation = split("1 * 2 + 5 * 3 * 8 + 4 / 18 + 42 < ( 11 - 1 ) * ( 4 + 7 * 2 )", ' ');
	printf("1 * 2 + 5 * 3 * 8 + 4 / 18 + 42 < ( 11 - 1 ) * ( 4 + 7 * 2 ) \n\n");
	three_address_code(equation);
	print_asm(assembly);
	return (0);
}
