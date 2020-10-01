


#include "../inc/database.h"
#include "../inc/semantic.h"
#include "../inc/compiler.h"

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

bool	check_next_token(t_hashtable *ff_list, char *next_token, char *current_token)
{
	char	*name;	
	char 	*value;	
	

	if (validate_id(current_token) == true)
		name = strdup("ID");
	else if (validate_literal(current_token) == true)
		name = strdup("LITERAL");
	else if (atoi(current_token))
		name = strdup("NUM");
	else
		name = strdup(current_token);
	printf("name is %s\n", name);
	value = ht_search(ff_list, name);
	if (value)
	{
		if (strcmp(value, "DONE") == 0)
			return (true);
		char *second;
		char **pieces = split(value, ' ');
		if (validate_id(next_token) == true)
			second = strdup("ID");
		else if (validate_literal(next_token) == true)
			second = strdup("LITERAL");
		else if (atoi(next_token))
			second = strdup("NUM"); 
		else
			second = strdup(next_token);
		
		if (value_found(second, pieces) == true)
			return (true);
	}
	return (false);
}

bool	semantic_analysis(t_token *tokens)
{
	t_token		*trav;
	char		**next;
	char		**start;
	t_hashtable	*ff_list;
	extern int max_number; // Scope value.

	//  init first and follow
	start = split("char const void struct int short double float size_t long longlong signed void", ' ');
        ff_list = first_and_follow();
	if (value_found(tokens->name, start) == false)
	{
		printf("Your code is shit and you deserve to die\n");
		return (false);
	}
	trav = tokens;	
	while (trav->next)
	{
		if (check_next_token(ff_list, trav->next->name, trav->name) == true)
			trav = trav->next;
		else
		{
			printf("This was a failed expedition\n");
			return (false);
		}
	}
	return (true);
}

