

#include "../inc/tac.h"
#include "../inc/intermediate.h"

void	print_as(t_code *assembly, int to, int togo)
{
	t_code	 *trav;


	trav = assembly;
	while (trav)
	{
		if (to == 1 && trav->line[0] != 't')
		{
			printf("cmp and jne L%d\n", togo);
			to = -1;
		}
		printf("%s\n", trav->line);
		trav = trav->next;
	}
	if (to == 1)
		printf("cmp and jne L%d\n", togo);
}

void	print_tac(t_block *blocks)
{
	t_block *trav;
	int to;
	
	to = -1;
	trav = blocks;
	while (trav->prev)
		trav = trav->prev;
	while (trav)
	{
		if (strcmp(trav->block, "IF") == 0 || strcmp(trav->block, "ELSEIF") == 0)
		{
			to = 1;
			printf("L%d:\n", trav->label);
		}
		else if (strcmp(trav->block, "WHILE") == 0)
		{
			printf("R%d:\n", trav->label);
		}
		print_as(trav->assembly, to, trav->togo);
		if (strcmp(trav->block, "IF") == 0 || strcmp(trav->block, "ELSEIF") == 0)
		{
			if (strcmp(trav->next->block, "LABEL") != 0)
			{
				printf("jmp L%d\n", trav->togo);
			}
		}
		to = -1;
		trav = trav->next;	
	}
}
