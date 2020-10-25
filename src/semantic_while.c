



#include "../inc/token.h"
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

t_token	*semantic_while(char *prev_name, t_token *token, t_hashtable *ff_list, bool do_trigger)
{
	t_token	*trav;
	t_token	*sub_sequence;
	t_token	*assignent;
	t_token *prev;
	int counter;
	extern char **start;
	char *prev_type;
	bool found;
	char *test;

	test = NULL;
	found = false;
	counter = 0;
	sub_sequence = NULL;
	trav = token;
	trav = trav->next;
	if (strcmp(trav->name, "(") == 0)
		trav = trav->next;
	
	while (trav && handle_native_csg(trav->name, trav->next->name) != SCOPE)
	{
		if (strcmp(trav->name, ")") == 0 && strcmp(trav->next->name, ";") == 0)
		{
			break ;
		}
		if (value_found(trav->name, start))
			printf("Error : variable declaration forbidden in while loops\n");
		if (trav->next && check_next_token(ff_list, trav->next->name, trav->name) == false)
			printf("unspecified error %s and %s\n", trav->name, trav->next->name);
		sub_sequence = push_token(sub_sequence, trav->name, trav->type,
			trav->line, trav->filename);
		prev = trav;
		trav = trav->next;
		counter++;	
	} 
	sub_sequence = push_token(sub_sequence, ";", "SEMICOLON", trav->line, trav->filename);
	t_token *h = sub_sequence;
	if (is_valid_equation(sub_sequence, ";"))
	{
		if (do_trigger == true && strcmp(trav->name, ";") != 0)
		{
			error_mode(trav, "do/while loop detected. Statement must end with a");
			
		}
		return (trav);
	}
	return (trav);
}













