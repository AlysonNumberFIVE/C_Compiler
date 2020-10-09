
#include "../inc/compiler.h"










t_token 	*error_recover(t_token *trav, char *message, t_token *recover)
{
	t_token *current;
	t_token *next;
	printf("BEFORE\n");
	recover->next = trav;
	printf("Error : %s\n", message);
	
	return (recover);
}

