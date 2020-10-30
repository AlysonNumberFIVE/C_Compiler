



typedef struct s_list {
	int n;
	struct s_list *next;
}	t_list;

t_list	*new_list(int n)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	new->n = n;
	new->next = NULL;
	return (new);
}
