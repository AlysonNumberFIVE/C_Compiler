

#include "../inc/parser.h"

t_token	*left = NULL;
t_token	*right = NULL;

bool	evaluate_equation(void)
{
	
}

bool	evaluate_literal(t_token *token)
{
	extern char *typing;

	if (typing && strcmp(typing, "ASSIGN") == 0)
	{
		if (token->next && equ_tokens(token->next->name) == true)
			return (false_error(token, 25));
		else if (token->next && sum_tokens(token->next->name) == true ||
			strcmp(token->next->name, ";") == true) 
			return (true);
	}
	return (false_error(token, 9));
}


