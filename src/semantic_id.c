
#include "../inc/semantic.h"
#include "../inc/compiler.h"

bool	handle_id(t_token *token)
{
	t_token *trav;
	extern t_db **list;
	char *to_check;

	trav = token;
	if (strcmp(trav->next->name, ";") == 0 || strcmp(trav->next->name, "=") == 0)
	{
		if (!(to_check = get_from_db(trav->name)))
		{
			printf("variable doesn't exist error\n");
			return (false);
		}
		trav = trav->next;
	}
	else if (strcmp(trav->next->name, "->") == 0)
	{
		if ((to_check = get_from_db
	}
	if (strcmp(trav->name, "=") == 0)
	{
	}
}
