

#include "../inc/compiler.h"
#include "../inc/tac.h"

void	print_tree(t_tree *ast)
{
	t_tree	*trav;
	t_token	*tok;

	trav = ast;
	while (trav)
	{
		tok = trav->tokens;
		printf(" %s\n", trav->type);
		while (tok)
		{
			printf(" %s ", tok->name);
			tok = tok->next;
		}
		printf("\n\n");
		trav = trav->next;
	}
}

void 	create_tac_structure(t_tree *ast)
{
	t_tree *trav;
	t_token	*token;
	int 	datatype;
	
	print_tree(ast);
	datatype = 0;
	trav = ast;
	/*
	while (trav)
	{
		token = ast->tokens;
		while (token)
		{

		}
	} */
}
