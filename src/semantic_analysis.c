

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




bool	validate_function(t_token *token)
{
	t_token 	*trav;
	char		*name;
	char		*type;
	char		*value;
	int		depth;
	extern int	max_number;
	extern t_db	*list;
	t_hashtable	*variables;

	depth = 0;
	value = NULL;
	type = NULL;
	name = NULL;
	trav = token;
	if (value_found(trav->name, start) == true)
	{
		type = strdup(trav->name);
		trav = trav->next;
	}
	else
	{
		printf("stdup %s\n", trav->next->name);
		printf("Datatype error\n");
		return (false);
	}
	
	while (strcmp(trav->name, "*") == 0)
	{
		depth++;
		trav = trav->next;
	}
	if (strcmp(trav->type, "ID") == 0)
	{
		name = strdup(trav->name);
		trav = trav->next;
	}
	else
	{
		printf("Incorrect variable naming\n");
		return (false);
	}

	if (strcmp(trav->name, ";") == 0)
	{
		printf("DONE\n");
		insert_into_db(type, name, NULL, depth);
	}
	else if (strcmp(trav->name, "(") == 0)
	{
		functions = push_function(functions, name, type, depth);
		if (strcmp(trav->next->name, "void") == 0 && strcmp(trav->next->next->name, ")") == 0 &&
			(strcmp(trav->next->next->next->name, ";") == 0 ||
			strcmp(trav->next->next->next->name, "{") == 0))
			return (true);
				
		trav = trav->next;
		char *pname;
		char *ptype;
		int pdepth;
		pname = NULL;
		ptype = NULL;
		pdepth = 0;
		t_fvars *variables;
		while (trav && strcmp(trav->name, ";") && strcmp(trav->name, "{"))
		{
			if (strcmp(trav->name, ",") == 0 || strcmp(trav->name, ")") == 0)
			{
				if (!pname || !ptype)
				{
					printf("error : incorrect variable naming convention\n");
					return (false);
				}
				variables = create_new_parameter(pname, ptype, depth);
				functions = new_parameter(functions, name, variables);
				param_free(variables);
				free_and_null(&pname);
				free_and_null(&ptype);
				pdepth = 0;
				if (strcmp(trav->name, ")") == 0)
				{
					trav = trav->next;
					break;
				}
				trav = trav->next;
			}
			else
			{
				if (value_found(trav->name, start) == true)
				{
					ptype = strdup(trav->name);
					trav = trav->next;
				}	
				else
				{
					printf("Incorrect way to create parameter vars\n");
					return (false);
				}
				while (trav && strcmp(trav->name, "*") == 0)
				{
					depth++;
					trav = trav->next;
				}
				if (strcmp(trav->type, "ID") == 0)
				{
					pname = strdup(trav->name);
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
	else if (strcmp(trav->name, "=") == 0)
	{
		trav = trav->next;
		value = value_checker(trav);
		insert_into_db(type, name, value, depth);
		//return (is_valid_equation(trav, ";"));
	}
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
	else if (token[0] == '\'' && token[strlen(token) - 1] == '\'')
		return (strdup("CHAR"));
	return (strdup(token));
}


bool	check_next_token(t_hashtable *ff_list, char *next_token, char *current_token)
{
	char	*name;	
	char 	*value;	
	char 	*second;
	char 	**pieces;	
	
	name = determine_token_type(current_token);
	value = ht_search(ff_list, name);
	if (value)
	{
		if (strcmp(value, "DONE") == 0)
			return (true);
		pieces = split(value, ' ');
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
	char		*prev;
	t_hashtable	*ff_list;
	t_token		*head;

	start = split("char const void struct int short double float size_t long longlong signed void", ' ');
        ff_list = first_and_follow();
	if (value_found(tokens->name, start) == false)
	{
		printf("Your code is shit and you deserve to die\n");
		return (false);
	}
	trav = tokens;	
	head = trav;
	while (trav)
	{
		if (handle_native_csg(prev, trav->name) == SCOPE
			 || strcmp(trav->name, ";") == 0)
		{
			validate_function(head);
			head = trav;
			trav = trav->next;
			if (head && strcmp(head->name, ";") == 0)
				head = head->next;
		}
		else if (check_next_token(ff_list, trav->next->name, trav->name) == true)
		{
			prev = trav->name;
			trav = trav->next;
		}
		else
		{
			printf("This was a failed expedition : %s\n", trav->name);
			// skipping entire line.
			while (trav)
			{
				if (strcmp(trav->name, ";") == 0)
					break;
				trav = trav->next;
			}
			trav = trav->next;
		}
	}
	print_variables();
	print_functions(functions);
	return (true);
}

