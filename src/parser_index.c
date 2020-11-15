


#include "../inc/parser.h"
#include "../inc/symbol.h"


t_current_var	*add_index_depth(t_current_var *list, int asterisk_count)
{
	t_current_var 	*trav;
	int		total;

	trav = list->next;
	if (strcmp(trav->str, "0") == 0)
	{
		free(trav->str);
		trav->str = itoa(asterisk_count);
	}
	else
	{
		total = atoi(trav->str) + asterisk_count;
		free(trav->str);
		trav->str = itoa(total);
	}
	return (list);
}
