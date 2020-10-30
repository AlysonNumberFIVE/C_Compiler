
#include "../inc/typedefs.h"
/*
typedef struct	s_typedef_list
{
	char *name;
	t_token *replace;
	struct s_typedef_list *next;
}	t_typedef;
*/

t_typedef	*typedef_list = NULL;
t_hashtable	*created_typedefs = NULL;

t_typedef	*new_typedef(char *name, t_token *segment)
{
	t_typedef	*new;

	new = (t_typedef *)malloc(sizeof(t_typedef));
	new->name = strdup(name);
	new->replace = segment;
	return (new);
}

t_typedef	*add_typedef(t_typedef *head, char *name, t_token *segment)
{
	t_typedef	*trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_typedef(name, segment);
	return (trav);
}

t_typedef	*push_typedef(t_typedef *head, char *name, t_token *segment)
{
	t_typedef 	*trav;

	trav = head;
	if (trav == NULL)
		trav = new_typedef(name, segment);
	else
	{
		trav = add_typedef(head, name, segment);
		trav = head;
	}
	return (trav);
}

t_token	*get_typedef(t_typedef *head, char *to_get)
{
	t_typedef	*trav;
	t_token		*section;
	t_token		*x;

	section = NULL;
	trav = head;
	while (trav)
	{
		if (strcmp(trav->name, to_get) == 0)
		{
			x = trav->replace;
			while (x)
			{
				section = push_token(section, x->name, x->type,
					x->line, x->filename);
				x = x->next;
			}
			break;
		}
		trav = trav->next;	
	}
	printf("aftewrmath\n");
	return (section);
}

t_token		*get_typedefd_struct_name(t_token *token, char **name)
{
	int brackets;

	brackets = 1;
	token = token->next;
	if (strcmp(token->name, "{") != 0)
	{
		if (strcmp(token->type, "ID") == 0)
		{
			*name = strdup(token->name);
			token = token->next;
			return (token);
		}
		else
		{
			printf("error\n");
			return (token);
		}
	}
	token = token->next;
	while (token->next && brackets > 0)
	{
		if (strcmp(token->name, "{") == 0)
			brackets++;
		else if (strcmp(token->name, "}") == 0)
			brackets--;
		token = token->next;
	}
	*name = strdup(token->name);
	token = token->next;
	return (token);
}

void		print_typedefs(t_typedef *head)
{
	t_typedef 	*trav;
	t_token		*seg;

	trav = head;
	while (trav)
	{
		printf(" name %s\n\t", trav->name);
		seg = trav->replace;
		while (seg)
		{
			printf(" %s ", seg->name);
			seg = seg->next;
		}
		printf("\n");
		trav = trav->next;
	}
}	

t_token 	*resolve(t_token *token)
{
	t_token	*segment;
	char	*name;

	segment = NULL;
	if (strcmp(token->name, "struct") == 0)
	{
		segment = push_token(segment, token->name, token->type,
			token->line, token->filename);
		token = token->next;
		if (strcmp(token->type, "ID") != 0)
			printf("failed\n");
		else
			segment = push_token(segment, token->name, token->type,
				token->line, token->filename);
		token = get_typedefd_struct_name(token, &name);	
	}
	else
	{
		while (token && strcmp(token->type, "ID") != 0)
		{
			segment = push_token(segment, token->name, token->type,
				token->line, token->filename);
			token = token->next;
		}
		name = strdup(token->name);
		token = token->next;
		if (!token || strcmp(token->name, ";") != 0)
		{
			printf("failed\n");
		}
	}
	typedef_list = push_typedef(typedef_list, name, segment);
	return (token);
}

t_token		*replace_section(t_token *token, t_token *prev)
{
	t_token	*next;
	t_token *section;

	next = token->next;
	section = get_typedef(typedef_list, token->name);
	prev->next = section;
	if (!section)
		printf("empty?\n");
	while (section->next)
		section = section->next;
	section->next = next;
	free(token->name);
	free(token->type);
	free(token->filename);
	free(token);
	token = next;
	return (token);	
}

bool		does_typedef_exist(char *name)
{
	t_typedef *trav;

	trav = typedef_list;
	while (trav)
	{
		if (strcmp(trav->name, name) == 0)
		{
			return (true);
		}
		trav = trav->next;
	}
	return (false);
}

t_token		*resolve_typedefs(t_token *token)
{
	t_token	*trav;
	char *name;
	t_token	*prev;

	prev = NULL;
	created_typedefs = create_table(500);
	trav = token;
	while (trav)
	{
		if (strcmp(trav->name, "typedef") == 0)
		{
			if (prev)
			{
				printf("prev\n");
				prev->next = trav->next;
			}
			else
			{
				printf("token\n");
				token = trav->next;
			}
			trav = trav->next;
			trav = resolve(trav);
			printf("after resolve()\n");
			if (!trav) break;
		}
		else if (does_typedef_exist(trav->name))
		{
			printf("Here we aer again\n");
			trav = replace_section(trav, prev);
			if (!trav) break ;
		}
		prev = trav;
		trav = trav->next;
	}
	while (token)
	{
		printf(" %s ", token->name);
		token = token->next;
	}	
	printf("\n\n\n");
	print_typedefs(typedef_list);
}
