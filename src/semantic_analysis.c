

#include "../inc/compiler.h"





bool	semantic_analysis(t_token *tokens)
{
	t_token	*trav;
	extern max_number; // Scope value.
	

	trav = tokens;
	while (trav)
	{
		if (strcmp(trav->name, "{") == 0)
			max_number++;
		else if (strcmp(trav->name, "}") == 0)
			max_number--;
		trav = trav->next;
	}
}

