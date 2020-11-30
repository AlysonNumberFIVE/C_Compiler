
#include "../inc/tac.h"

t_tree	*new_tree(char *type, t_token *token, int scope)
{
	t_tree *tree;
	
	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->type = strdup(type);
	tree->tokens = token;
	tree->scope = scope;
	tree->next = NULL;
	return (tree);
}

t_tree	*add_tree(t_tree *head, char *type, t_token *tokens, int scope)
{
	t_tree *trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_tree(type, tokens, scope);
	return (trav);
}

t_tree	*push_tree(t_tree *head, char *type, t_token *tokens, int scope)
{
	t_tree	*trav;

	trav = head;
	if (trav == NULL)
	{
		trav = new_tree(type, tokens, scope);
	}
	else
	{
		trav = add_tree(head, type, tokens, scope);
		trav = head;
	}
	return (trav);
}

char	*get_syntactic_name(t_token *token)
{
	char *type;
	t_token *trav;
	if (token->next)
	{
		if (strcmp(token->name, "else") == 0 &&
			strcmp(token->next->name, "if") == 0)
			return (strdup("ELSEIF"));
		else if (strcmp(token->name, "while") == 0)
			return (strdup("WHILE"));
		else if (strcmp(token->name, "if") == 0)
			return (strdup("IF"));
		else if (strcmp(token->name, "else") == 0)
			return (strdup("ELSE"));
		trav = token;
		
		type = strdup(trav->type);
		while (trav && strcmp(trav->type, "ID") != 0)
			trav = trav->next;
		if (!trav)
			return (strdup("NONE"));
		if (trav->next && strcmp(trav->next->name, "(") == 0 &&
			strcmp(type, "DATATYPE") != 0)
			return (strdup("CALL"));
		else if (trav->next && strcmp(trav->next->name, "(") == 0 &&
			strcmp(type, "DATATYPE") == 0)
			return (strdup("LABEL"));
		else if (trav->next && strcmp(trav->next->name, "=") == 0)
			return (strdup("ASSIGN"));
		else if (trav->next && strcmp(trav->next->name, ";") == 0)
			return (strdup("CREATE"));
	}
	return (strdup("NONE"));
}






