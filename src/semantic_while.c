




#include "../inc/compiler.h"
#include "../inc/semantic.h"


bool	assignment_tokens(char *to_check)
{
	char array[10][10] = {
		"<<=\0",
		">>=\0",
		"|=\0",
		"&=\0",
		"=\0",
		"=\0"
	};
	int counter;
	
	counter = 0;
	while (counter < 6)
	{
		if (strcmp(array[counter], to_check) == 0)
			return (true);
		counter++;
	}
	return (true);
}

t_token	*semantic_while(char *prev, t_token *curr)
{
	t_token	*trav;
	t_token	*sub_sequence;
	t_token	*assignent;
	int counter;
	char *prev_type;
	bool found;
	char *test;

	test = NULL;
	found = false;
	counter = 0;
	sub_sequence = NULL;
	trav = token;
	while (trav && handle_native_csg(prev, trav->name))
	{
		if (counter == 1)
		{
			if (assignment_token(trav->name) == true)
				found == true;
			if (found == true && strcmp(prev_type, "ID") != 0)
			{
				printf("error: lvalue has to be a variable\n");
				return (trav);		
			}
		}
		else if (assignment_token(trav->name) == true && counter != 1)
		{
			printf("error : can't have more than 1 assigment token\n");
			return (trav);
		}
		else if (found == true)
			assignment = push_token(assignment, trav->name, trav->type);
		sub_sequence = push_token(sub_sequence, trav->name, trav->type);
		sprev_type = trav->type;
		trav = trav->next
		counter++;	
	} 
	if (assignment)
	{
		test = get_from_db(sub_sequence->name);
		if (test)
		{
			if (is_valid_equation(assignment))
				return (true);
			else
			{
				printf("invalid equation\n");
				return (false);
			}		
		}
		else
		{
			printf("error: variable doesn't exist\n");
			return (false);
		}
	}
	if (is_valid_equation(sub_sequence))
		return (true);
	printf("error: invalid euqation\n");
	return (false);
}












