

#include "../inc/compiler.h"

typedef struct	s_typedef_list
{
	char *name;
	t_token *replace;
}	t_typedef;

	

t_token		*resolve_typedefs(t_token *token)
{
	t_token	*trav;

	trav = token;
	while (trav)
	{
		if (strcmp(trav->name, "tyepedef") == 0)
		{
			trav = resolve_typedef;
		}
	}
}
