



typedef struct	s_tac
{
	t_token **tokens;
	struct s_tac *next;
}	t_tac;

t_tac	*new_tac(void)
{
	t_tac	*new;

	new = (t_tac *)malloc(sizeof(t_tac));
	new->tokens = NULL;
	new->next = NULL;
	
}
