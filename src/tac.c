

#include "../inc/compiler.h"
#include "../inc/tac.h"

int	if_depth = 0;
char	**token_to_2d(t_token *token)
{
	char **list;
	int 	brackets;

	brackets = 1;
	token = token->next->next;
	list = NULL;
	while (token)
	{
		if (strcmp(token->name, "(") == 0)
			brackets++;
		else if (strcmp(token->name, ")") == 0)
			brackets--;
		if (brackets == 0)
			break;
		list = arraypush(list, token->name);
		token = token->next;
	}
	return (list);
}

void	print_tree(t_tree *ast)
{
	t_tree	*trav;
	t_token	*tok;

	trav = ast;
	while (trav)
	{
		tok = trav->tokens;
		printf(" %s : depth : %d\n", trav->type, trav->scope);
		while (tok)
		{
			printf(" %s ", tok->name);
			tok = tok->next;
		}
		printf("\n\n");
		trav = trav->next;
	}
}


void	call_stack(t_token *token)
{
	t_token *trav;
	char **stack;
	char *param;
	int brackets;
	int i;

	brackets = 1;
	stack = NULL;
	param = (char *)malloc(sizeof(char));
	stack = arraypush(stack, token->name);
	token = token->next->next;
	trav = token;
	while (trav)
	{
		if (strcmp(trav->name, "(") == 0)
			brackets++;
		else if (strcmp(trav->name, ")") == 0)
			brackets--;
		if (brackets == 0)
			break;
		if (strcmp(trav->name, ",") == 0)
		{
			stack = arraypush(stack, param);		
			param = NULL; 
		}
		else
		{
			param = join(param, " ");
			param = join(param, trav->name);
		}
		trav = trav->next;
	}
	stack = arraypush(stack, param);
	
	i = arraylen(stack) - 1;
	while (i > 0)
	{
		printf("push %s\n", stack[i]);
		i--;
	}
	printf("call %s\n", stack[0]);
}


void	if_test(t_token *tokens, int depth)
{
	extern t_code *assembly;
	char **list;

	printf("L%d:\n", if_depth);
	list = token_to_2d(tokens);
	three_address_code(list);
	print_asm(assembly);
	printf("jne L%d\n", if_depth + 1);
	if_depth++;
}

void	while_test(t_token *tokens, int depth)
{
	t_token	*trav;
	extern t_code *assembly;
	char **list;
	
	trav = tokens;
	printf("R%d:\n", depth);
	list = token_to_2d(trav);
	three_address_code(list);
	print_asm(assembly);
	printf("cmp\n");
	printf("jne L%d:\n", depth - 1);
}	

void 	create_tac_structure(t_tree *ast)
{
	t_tree *trav;
	t_token	*token;
	int 	datatype;
	
//	print_tree(ast);
	datatype = 0;
	trav = ast;
	while (trav)
	{
		token = trav->tokens;
		print_linear(token);
		if (strcmp(trav->type, "WHILE") == 0)
			while_test(token, trav->scope);
		else if (strcmp(trav->type, "CALL") == 0)
			call_stack(token);
		else if (strcmp(trav->type, "IF") == 0)
			if_test(token, trav->scope);
		else if (strcmp(trav->type, "ELSEIF") == 0)
		{
			token = token->next;
			if_test(token, trav->scope);
		}
		trav = trav->next;
	} 
}
