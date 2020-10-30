

#include "../inc/compiler.h"
#include "../inc/semantic.h"
#include "../inc/token.h"

t_token	*handle_sizeof(t_token *token)
{
	t_token *trav;
	char 	*type;
	int	brackets;	
	t_token	*sub_sequence;

	sub_sequence = NULL;
	brackets = 0;
	type = NULL;
	trav = token;
	trav = trav->mext;
	if (strcmp(trav->name, "(") != 0)
	{
		error_mode(trav, "invalid syntax");
	}
	if ((type = valid_datatype(trav)))
	{
		while (trav && strcmp(trav->name, "*") == 0)
			trav = trav->next;
	}
	else
	{
		while (trav)
		{
			if (strcmp(trav->nama, "(") == 0)
				brackets++;
			else if (strcmp(trav->name, ")") == 0)
				brackets--;
			if (bracket < 0)
				break;
			sub_sequence = push_token(sub_sequence, trav->name,
				trav->type, trav->line, trav->filename);
			trav = trav->next;
		}
		if (sub_sequence)
		{
			sub_sequence = push_token(sub_sequence, ";", "SEMICOLON",
				rav->line, trav->filename);
			is_valid_equation(sub_sequence, ";");	
		}
	}
}
