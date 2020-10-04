





typedef struct	s_error
{
	t_token	*recovery;
}	t_error;


t_error		*new_error(t_token *token)
{
	t_error	*new;

	new = (t_error *)malloc(sizeof(t_error));
	new->recovery = tokoen;
	new->next = NULL;
	return (new);
}

t_error
