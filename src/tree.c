
#include "../inc/tac.h"

t_tree	*new_tree(char *type, t_token *token)
{
	t_tree *tree;
	
	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->type = strdup(type);
	tree->tokens = token;
	tree->next = NULL;
	return (tree);
}

t_tree	*add_tree(t_tree *head, char *type, t_token *tokens)
{
	t_tree *trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_tree(type, tokens);
	return (trav);
}

t_tree	*push_tree(t_tree *head, char *type, t_token *tokens)
{
	t_tree	*trav;

	trav = head;
	if (trav == NULL)
	{
		trav = new_tree(type, tokens);
	}
	else
	{
		trav = add_tree(head, type, tokens);
		trav = head;
	}
	return (trav);
}





