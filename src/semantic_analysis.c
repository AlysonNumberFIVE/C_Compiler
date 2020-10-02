

#include <ctype.h>
#include "../inc/database.h"
#include "../inc/semantic.h"
#include "../inc/compiler.h"

t_function *functions = NULL;
t_token	*to_evaluate = NULL;
char	**start = NULL;

bool	value_found(char *value, char **to_scan)
{
	int		i;

	i = 0;
	while (to_scan[i])
	{
		if (strcmp(value, to_scan[i]) == 0)
			return (true);
		i++;
	}
	return (false);
} 



bool	validate_literal(char *str)
{
	if (str[0] == '\"' && str[strlen(str) - 1] == '\"')
		return (true);
	return (false);
}

bool	validate_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}


bool	validate_function(t_token *list)
{
	t_token 	*trav;
	char		*name;
	char		**parameters;	
	t_hashtable	*variables;

	parameters = NULL;
	name = NULL;
	trav = list;
	if (value_found(trav->name, start) == true)
		trav = trav->next;
	else
	{
		printf("Datatype error\n");
		return (false);
	}
	
	while (strcmp(trav->name, "*") == 0)
		trav = trav->next;

	if (strcmp(trav->type, "ID") == 0)
		trav = trav->next;
	else
	{
		printf("Incorrect variable naming\n");
		return (false);
	}

	if (strcmp(trav->name, ";") == 0)
		printf("create variable with no value\n");

	else if (strcmp(trav->name, "(") == 0)
	{
		trav = trav->next;
		char *value;
		value = (char *)malloc(sizeof(char));
		while (trav && strcmp(trav->name, ";") && strcmp(trav->name, "{"))
		{
			if (strcmp(trav->name, ",") == 0 || strcmp(trav->name, ")") == 0)
			{
				parameters = arraypush(parameters, value);
				free(value);
				value = NULL;
				if (strcmp(trav->name, ")") == 0)
					break;
			}
			else
			{
				if (value_found(trav->name, start) == true)
				{
					value = join(value, trav->name);
					trav = trav->next;
				}	
				else
				{
					printf("Incorrect way to create parameter vars\n");
					return (false);
				}
				while (trav && strcmp(trav->name, "*") == 0)
				{
					value = join(value, trav->name);
					trav = trav->next;
				}
				if (strcmp(trav->type, "ID") == 0)
				{
					value = join(value, trav->name);
					trav = trav->next;

				}
				else
				{
					printf("Incorrect variable naming\n");	
					return (false);
				}
			}
		}	
	}
	printf("here we go\n");
	return (true);
}


char	*determine_token_type(char *token)
{
	if (validate_id(token) == true)
		return (strdup("ID"));
	else if (validate_literal(token) == true)
		return (strdup("LITERAL"));
	else if (validate_num(token) == true)
		return (strdup("NUM"));
	return (strdup(token));
}


bool	check_next_token(t_hashtable *ff_list, char *next_token, char *current_token)
{
	char	*name;	
	char 	*value;	
	
	
	name = determine_token_type(current_token);
	printf("name is %s\n", name);
	value = ht_search(ff_list, name);
	if (value)
	{
		if (strcmp(value, "DONE") == 0)
			return (true);
		char *second;
		char **pieces = split(value, ' ');
		second = determine_token_type(next_token);
		if (value_found(second, pieces) == true)
			return (true);
	}
	return (false);
}

bool	semantic_analysis(t_token *tokens)
{
	t_token		*trav;
	char		**next;
	t_hashtable	*ff_list;
	extern int max_number; // Scope value.
	t_token		*head;

		//  init first and follow
	start = split("char const void struct int short double float size_t long longlong signed void", ' ');
        ff_list = first_and_follow();
	if (value_found(tokens->name, start) == false)
	{
		printf("Your code is shit and you deserve to die\n");
		return (false);
	}
	trav = tokens;	
	head = trav;
	while (trav->next)
	{
		if (strcmp(trav->name, "{") == 0 || strcmp(trav->name, ";") == 0)
		{
			validate_function(head);

			trav = trav->next;
			head = trav;	
			printf("process variable/function\n");
		}
		else if (check_next_token(ff_list, trav->next->name, trav->name) == true)
			trav = trav->next;
		else
		{
			printf("This was a failed expedition\n");
			return (false);
		}
	}
	return (true);
}

