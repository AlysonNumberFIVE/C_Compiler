

#include "../inc/compiler.h"
#include "../inc/tac.h"

int	if_depth = 0;
int 	elseif = 0;
int	current = 0;
t_block	*blocks = NULL;
int	labelname = 0;
int	loopcount = 0;
int 	size = 0;

t_code	*copy_asm(t_code *assembly)
{
	t_code	*new;
	t_code	*trav;

	new = NULL;
	trav = assembly;
	while (trav)
	{
		new = push_line(new, trav->line_number, trav->line);
		trav = trav->next;
	}
	return (new);
}

char	**token_to_2d(t_token *tokens)
{
	char **list;
	int 	brackets;
	t_token	*token;

	brackets = 1;
	token = tokens->next->next;
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
	extern t_code *assembly;
	int i;

	brackets = 1;
	stack = NULL;
	param = (char *)malloc(sizeof(char));
	stack = arraypush(stack, token->name);
	trav = token->next->next;
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
			param = (char *)malloc(sizeof(char)); 
		}
		else
		{
			param = join(param, " ");
			param = join(param, trav->name);
		}
		trav = trav->next;
	}
	if (param)
		stack = arraypush(stack, param);
	
	i = arraylen(stack) - 1;
	while (i > 0)
	{
		blocks->assembly = push_line(blocks->assembly, 0, join("push ", stack[i]));
		printf("push %s\n", stack[i]);
		i--;
	}
	blocks->assembly = push_line(blocks->assembly, 0, join("call ", stack[0]));
	printf("call %s\n", stack[0]);
//	blocks->assembly = copy_asm(assembly);
	assembly = NULL;
}


t_token	*skip(t_token *token)
{
	int brackets;

	brackets = 1;
	token = token->next->next;
	while (token)
	{
		printf(" t : %s\n", token->name);
		if (strcmp(token->name, "(") == 0)
			brackets++;
		else if (strcmp(token->name, ")") == 0)
			brackets--;
		if (brackets == 0)
			break;
		token = token->next;
	}
	return (token);
}
void 	if_test(t_token *tokens, int depth);
void	while_test(t_token *tokens, int depth);

void	resolve(t_token *token, int depth)
{
	extern t_code *assembly;
	token = token->next;
	if (strcmp(token->name, "if") == 0)
	{
		assembly = NULL;
		blocks = push_block(blocks, "IF", labelname, -1, depth);
		labelname++;
		if_test(token, depth);
	}
	else if (strcmp(token->name, "while") == 0)
	{
		assembly = NULL;
		while_test(token, depth + 1);
	}
	else if (strcmp(token->name, "else") == 0)
	{
		token = token->next;
		if (strcmp(token->name, "if") == 0)
		{
			blocks = push_block(blocks, "ELSEIF", labelname, -1, depth);
			blocks = patch_elseif(blocks);
			labelname++;
			if_test(token, depth);
		}
		else
		{
			blocks = push_block(blocks, "ELSE", labelname, -1, depth);
			blocks = patch_elseif(blocks);
			labelname++;
			if_test(token, depth);
		}	
	}
	else if (token->next && strcmp(token->next->name, "(") == 0)
	{
		call_stack(token);
	}
}

void	if_test(t_token *tokens, int depth)
{
	extern t_code *assembly;
	char **list;

	printf("L%d:\n", depth); 
	list = token_to_2d(tokens);
	three_address_code(list);
	blocks->assembly = copy_asm(assembly);
//	print_asm(assembly);
	printf("jne L%d\n", depth + 1);
	tokens = skip(tokens);
	resolve(tokens, depth);
	if_depth++;
	assembly = NULL;
}

void	label_test(t_token *tokens, int depth)
{
	t_token	*trav;
	char **list;
	extern t_code *assembly;

	trav = tokens->next;
//	list = token_to_2d(tokens);
//	three_address_code(list);

	printf("LABEL TRAV IS %s\n", trav->name);
	blocks->assembly = push_line(blocks->assembly, 0, join(trav->name, ":"));
	tokens = skip(trav);
	resolve(tokens, depth);
	assembly = NULL;
}

void	assign_test(t_token *token, int depth)
{
	char **list;
	extern t_code *assembly;
	if (strcmp(token->type, "DATATYPE") == 0)
		token = token->next;
	blocks->assembly = push_line(blocks->assembly, 0, 
		join(join(token->name, " = "),token->next->next->name)); 
	resolve(token, depth);
	assembly = NULL;
}

void	while_test(t_token *tokens, int depth)
{
	t_token	*trav;
	extern t_code *assembly;
	char **list;
	
	trav = tokens;
//	printf("R%d: (depth: %d)\n", depth, depth);
	list = token_to_2d(trav);
	three_address_code(list);
	blocks->assembly = copy_asm(assembly);
//	print_asm(assembly);
	tokens = skip(tokens);
	printf("cmp\n");
	printf("jne L%d:\n", depth - 1);
	resolve(tokens, depth);
	assembly = NULL;
}	


void 	create_tac_structure(t_tree *ast)
{
	t_tree *trav;
	t_token	*token;
	int 	datatype;
	char 	*type;
	int 	depth;
	
	type = NULL;
//	print_tree(ast);
	datatype = 0;
	trav = ast;
	while (trav)
	{
		token = trav->tokens;
		printf("%d  %s :", trav->scope, trav->type); print_linear(token);
		trav->scope += size;
		if (strcmp(trav->type, "WHILE") == 0)
		{
			blocks = push_block(blocks, "WHILE", loopcount, -1, trav->scope);
			blocks = patch_elseif(blocks);
			loopcount++;
			while_test(token, trav->scope);
		}
		else if (strcmp(trav->type, "CALL") == 0)
		{
			call_stack(token);
		}
		else if (strcmp(trav->type, "IF") == 0)
		{
			blocks = push_block(blocks, "IF", labelname, -1, trav->scope - 1);
			labelname++;
			if_test(token, trav->scope);
		}
		else if (strcmp(trav->type, "ELSEIF") == 0)
		{
			blocks = push_block(blocks, "ELSEIF", labelname, -1, trav->scope);
			blocks = patch_elseif(blocks);
			token = token->next;
			labelname++;
			if_test(token, current);
		}
		else if (strcmp(trav->type, "ELSE") == 0)
		{
			blocks = push_block(blocks, "ELSE", labelname, -1, trav->scope);
			blocks = patch_elseif(blocks);
			
		}
		else if (strcmp(trav->type, "LABEL") == 0)
		{
			size++;
			blocks = push_block(blocks, "LABEL", labelname, -1, 1);
			label_test(token, trav->scope);
		}
		else if (strcmp(trav->type, "ASSIGN") == 0)
		{
			blocks = push_block(blocks, "ASSIGN", labelname, -1, trav->scope);
			assign_test(token, trav->scope);
		}
		trav = trav->next;
	}
	print_blocks(blocks);
	print_tac(blocks); 
}
