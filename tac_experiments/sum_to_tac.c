




typedef struct s_stack_vars
{
	char *label;
	int pos;
	struct s_stack_vars *next;
}	t_stack_v;

t_stack_v	*stack_vars = NULL;
t_stack_v	*new_svar(char *label, int pos)
{
	t_stack_v 	*new;

	new = (t_stack_v *)malloc(sizeof(t_stack_v));
	new->label = strdup(label);
	new->pos = pos;
	new->next = NULL;
	return (new);
}

t_stack_v	*add_svar(t_stack_v *head, char *label, int pos)
{
	t_stack_v	*trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_svar(label, post);
	return (trav);
}

t_stack_v	*push_svar(t_stac_v *head, char *label, int pos)
{
	t_stack_v	*trav;

	trav = head;
	if (trav == NULL)
		trav = new_svar(label, post);
	else
	{
		trav = add_svar(head, label, pos);
		trav = head;
	}
	return (trav);
}

t_stack_v	*finder(char *name)
{
	
}

void 	function_call(t_token *token)
{
	t_tokne *trav;
	char *statement;
	char *underscore;
	int pos;

	pos = 0;
	stack_vars = NULL;
	while (trav && strcmp(trav->type, "ID") != 0)
		trav = trav->next;
	underscore = strdup("_");
	statement = join(underscore, trav->name);
	statement = join(statement, ":\n");
	
	trav = trav->next;
	if (strcmp(trav->name, "(") == 0)
		trav = trav->next;
	while (trav)
	{
		while (trav && strcmp(trav->type, "ID") != 0 || strcmp(trav->name, ")") != 0)
			trav = trav->next;
		if (strcmp(trav->type, "ID") == 0)
		{
			pos++;
			stack_vars = push_svars(stack_svars, trav->name, pos);
			trav = trav->next;
		}
		if (strcmp(trav->name, ",") == 0)
			trav = trav->next;
		else
			break ;
	}
	trav = trav->next;
	printf("%s ", statement);
}

void	one_line(t_token *token)
{
	t_token *trav;
	char *last;

	trav = token;
	if (strcmp(trav->name, "*") == 0)
	{
		trav = trav->next;
		while (trav && strcmp(trav->name, "*") == 0)
			trav = trav->next;
		
	}
	
}









