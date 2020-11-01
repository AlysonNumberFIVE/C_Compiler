



struct s_list {
	int n;
	struct s_list *next;
};
void	*malloc(int x)
{
	return ("null");
}
void	*new_list(int n)
{
	struct s_list *new;

	new = (void *)malloc(42);
	new->n = 1;
	new->next = NULL;
	return (new);
}
