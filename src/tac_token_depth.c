


#include "../inc/tac.h"


t_td	*new_td(char *type, int depth)
{
	t_td *head;

	head = (t_td *)malloc(sizeof(t_td));
	head->type = strdup(type);
	head->depth = depth;
	head->next = NULL;
	return (head);
}

t_td	*add_td(t_td *head, char *type, int depth)
{
	t_td *trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_td(type, depth);
	return (trav);
}

t_td	*push_td(t_td *head, char *type, int depth)
{
	t_td *trav;
	
	trav = head;
	if (trav == NULL)
	{
		trav = new_td(type, depth);
	}
	else
	{
		trav = add_td(head, type, depth);
		trav = head;
	}
	return (trav);
}




