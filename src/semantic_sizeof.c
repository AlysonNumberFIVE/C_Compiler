

#include "../inc/compiler.h"
#include "../inc/semantic.h"
#include "../inc/token.h"

t_token	*semantic_sizeof(t_token *token)
{
	t_token *trav;
	char 	*type;
	int	brackets;	
	t_token	*prev;
	t_token	*sub_sequence;

	sub_sequence = NULL;
	brackets = 0;
	type = NULL;
	trav = token;
	trav = trav->next;
	if (strcmp(trav->name, "(") != 0)
	{
		error_mode(trav, "invalid syntax");
	}
	else
		brackets = 1;
	if ((type = valid_datatypes(trav)))
	{
		while (trav && strcmp(trav->name, "*") == 0)
			trav = trav->next;
	}
	else
	{
		trav = trav->next;
		while (trav)
		{
			if (strcmp(trav->name, "(") == 0)
				brackets++;
			else if (strcmp(trav->name, ")") == 0)
				brackets--;
			if (brackets <= 0)
				break;
			sub_sequence = push_token(sub_sequence, trav->name,
				trav->type, trav->line, trav->filename);
			prev = trav;
			trav = trav->next;
		}
	//	trav = trav->next;
		if (sub_sequence)
		{
			t_token *h = sub_sequence;
			while (h)
			{
				printf(">  %s ", h->name);
				h = h->next;
			}
			printf("\n\n");
			sub_sequence = push_token(sub_sequence, ";", "SEMICOLON",
				trav->line, trav->filename);
			is_valid_equation(sub_sequence, ";");	
		}
	}
	return (trav);
}
