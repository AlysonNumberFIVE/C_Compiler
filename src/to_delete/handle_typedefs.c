

typedef struct s_typedefs
{
	int	datatype // the size of the 
}

t_hashtable	*handle_typedef(t_token *token)
{
	t_token	*trav;
	char	*replace;

	trav = token;
	if (strcmp(trav->name, "struct") == 0)
	{
		printf("run struct code\n");
	}
	else
	{
				
	}
}
