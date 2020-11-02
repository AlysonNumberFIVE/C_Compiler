
#include "../inc/compiler.h"





t_token		*forward_recovery(t_token *trav, char *message, t_token *recover)
{
	t_token	*next;
	t_token *current;

	current = trav;
	next = trav->next;
	trav->next = recover;
	recover->next = next;
	printf("Error : %s\n", message);
	return (trav);
}




t_token 	*error_recover(t_token *trav, char *message, t_token *recover)
{
	t_token *current;
	t_token *next;
	recover->next = trav;
	printf("Error : %s\n", message);
	
	return (recover);
}

