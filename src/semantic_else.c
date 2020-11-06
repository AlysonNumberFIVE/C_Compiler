

#include "../inc/compiler.h"
#include "../inc/semantic.h"

t_token *semantic_else(char *prev_name, t_token *token, t_hashtable *ff_list)
{
	t_token *trav;
	
	trav = token;
	trav = trav->next;
	if (trav && strcmp(trav->name, "if") == 0)
	{
		return (semantic_if(trav->name, trav, ff_list));
	}
	else if (trav && strcmp(trav->name, "{") == 0)
	{
		return (trav);
	}

	error_mode(trav, "Syntax error (else statement)");
	return (trav);
}
