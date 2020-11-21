

#include "../inc/parser.h"
#include "../inc/symbol.h"

int	forloop_count = 0;
bool	inside_for = false;
bool	inside_loop = false;
bool	inside_do = false;


bool	evaluate_for(t_token *token)
{
	printf("FOR LOOP\n");
	inside_for = true;
	if (token->next && strcmp(token->next->name, "(") == 0)
		return (true);
	return (false_error(token, 10));
}

bool	evaluate_return(t_token *token)
{
	if (token->next && strcmp(token->next->name, "(") == 0 ||
		strcmp(token->next->type, "NUM") == 0 ||
		strcmp(token->next->type, "ID") == 0)
		return (true);
	return (false_error(token, 10));
}

bool	evaluate_while(t_token *token)
{
	if (token->next && strcmp(token->next->name, "(") == 0)
		return (true);
	return (false_error(token, 10));
}

bool	evaluate_do(t_token *token)
{
	inside_do = true;
	if (token->next && strcmp(token->next->name, "{") == 0)
		return (true);
	else if (strcmp(token->next->type, "DATATYPE") == 0 ||
           strcmp(token->next->name, "*") == 0 ||
           strcmp(token->next->name, "}") == 0 ||
           strcmp(token->next->name, "NUM") == 0)
           return (true);
	return (false_error(token, 10));
}
