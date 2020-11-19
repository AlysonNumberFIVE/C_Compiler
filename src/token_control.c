
#include "../inc/compiler.h"

t_token *new_token(char *name, char *type, size_t line, char *filename)
{
    t_token *new;

    new = (t_token *)malloc(sizeof(t_token));
    new->name = strdup(name);
    new->type = strdup(type);
    new->filename = strdup(filename);
    new->line = line;
    new->next = NULL;
    return (new);
}

t_token *add_token(t_token *first, char *name, char *type, size_t line, char *filename)
{
    t_token *last;

    last = first;
    while (last->next)
        last = last->next;
   // last->next = new_token(name, type, line, filename);
    
    last->next = (t_token *)malloc(sizeof(t_token));
    last->next->name = strdup(name);
    last->next->type = strdup(type);
    last->next->filename = strdup(filename);
    last->next->line = line;
    last->next->next = NULL;
     
    return (last);
}

t_token *push_token(t_token *first, char *name, char *type, size_t line, char *filename)
{
    t_token *last;

    last = first;
    if (last == NULL)
    {
        last = new_token(name, type, line, filename);
    }
    else
    {
        last = add_token(first, name, type, line, filename);
        last = first;
    }
    return (last);
}

void	free_tokens(t_token *token)
{
	t_token	*trav;

	while (token)
	{
		trav = token;
		token = token->next;
		free(trav->name);
		free(trav->type);
		free(trav->filename);
		free(trav);
	}
}
