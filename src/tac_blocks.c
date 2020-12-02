

#include "../inc/intermediate.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/tac.h"
/*
typedef struct	s_blocks
{
	char 	*block;
	int	label;
	int	togo;
	int 	depth;
	struct s_blocks *next;
	struct s_blocks	*prev;
}	t_block;
*/

t_block	*new_block(char *block, int label, int togo, int depth)
{
	t_block	*new;

	new = (t_block *)malloc(sizeof(t_block));
	new->block = strdup(block);
	new->label = label;
	new->togo = togo;
	new->depth = depth;
	new->assembly = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_block	*add_block(t_block *head, char *block, int label, int togo, int depth)
{
	t_block	*trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_block(block, label, togo, depth);
	trav->next->prev = trav;
	trav = trav->next;
	return (trav);
}

t_block	*push_block(t_block *head, char *block, int label, int togo, int depth)
{
	t_block	*trav;

	trav = head;
	if (trav == NULL)
	{
		trav = new_block(block, label, togo, depth);
	}
	else
	{
		trav = add_block(head, block, label, togo, depth);
	}
	return (trav);
}

t_block	*patch_elseif(t_block *block)
{
	int save_togo;
	int save_depth;
	t_block *trav;	

	save_depth = block->depth;
	save_togo = block->label;
	trav = block->prev;
	while (trav)
	{
		if (trav->depth == save_depth)
		{
			trav->togo = save_togo;
			break;
		}
		trav = trav->prev; 
	}
	return (block);
}

void	print_tabs(int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		printf("\t");
		j++;
	}
}



void	print_blocks(t_block *blocks)
{
	t_block	*trav;

	trav = blocks;
	while (trav->prev)
		trav = trav->prev;
	while (trav)
	{
		print_tabs(trav->depth); printf("name  :%s\n", trav->block);
		print_tabs(trav->depth); printf("label :%d\n", trav->label);
		print_tabs(trav->depth); printf("togo  :%d\n", trav->togo);
		print_tabs(trav->depth); printf("depth :%d\n", trav->depth);

		print_tabs(trav->depth); printf("asm: \n");
		t_code *nest;
		nest = trav->assembly;
		while (nest)
		{
			print_tabs(trav->depth);printf("%s\n", nest->line);
			nest = nest->next;
		}
		printf("\n\n");
		trav = trav->next;
	}
}

/*
int	main(void)
{
	t_block *blocks = NULL;

	blocks = push_block(blocks, "IF", 1, -1, 1);
	blocks = push_block(blocks, "IF", 2, -1, 2);
	blocks = push_block(blocks, "IF", 3, -1, 3);
	blocks = push_block(blocks, "ELSEIF", 4, -1, 2);
	blocks = patch_elseif(blocks);
	blocks = push_block(blocks, "IF", 5, -1, 3);
	blocks = push_block(blocks, "ELSEIF", 6, -1, 2);
	blocks = patch_elseif(blocks);
	print_blocks(blocks);

	blocks = push_block(blocks, "WHILE", 7, -1, 1);
	blocks = push_block(blocks, "IF", 8, -1, 2);
	
	return (0);
}

*/


	

















