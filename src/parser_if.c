


#include "../inc/compiler.h"
#include "../inc/parser.h"
#include "../inc/symbol.h"


bool	in_function = false;


bool	evaluate_else(t_token *token)
{
	extern int scope_depth;

	if (scope_depth < 1) return (false_error(token, 10));
	if (token->next && strcmp(token->next->name, "if") == 0 ||
		strcmp(token->next->name, "{") == 0)
		return (true);
	else if (strcmp(token->next->type, "DATATYPE") == 0 ||
          	 strcmp(token->next->name, "*") == 0 ||
          	 strcmp(token->next->name, "NUM") == 0 ||
          	strcmp(token->next->name, "ID") == 0)
           return (true);
}

bool	evaluate_if(t_token *token)
{
	extern int scope_depth;

	if (scope_depth < 1)  return (false_error(token, 10));
	if (token->next && strcmp(token->next->name, "(") == 0)
		return (true);
	return (false_error(token, 9));	
}
