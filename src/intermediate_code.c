

#include "../inc/intermediate.h"


t_code	*new_line(int line_number, char *line)
{
	t_code	*new;

	new = (t_code *)malloc(sizeof(t_code));
	new->line_number = line_number;
	new->line = strdup(line);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_code	*add_line(t_code *head, int line_number, char *line)
{
	t_code	*trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_line(line_number, line);
	trav->prev = trav;
	return (trav);	
}

t_code	*push_line(t_code *head, int line_number, char *line)
{
	t_code *trav;

	trav = head;
	if (trav == NULL)
	{
		trav = new_line(line_number, line);
	}
	else
	{
		trav = add_line(head, line_number, line);
		trav = head;
	}
	return (trav);
}

