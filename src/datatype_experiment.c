

#include "../inc/compiler.h"
#include "../inc/semantic.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "../inc/token.h"

char 	**legal_combinations(void)
{
	char **array;

	array = NULL;

	array = arraypush(array, "int");
	array = arraypush(array, "long");
	array = arraypush(array, "void");
	array = arraypush(array, "float");
	array = arraypush(array, "size_t");
	array = arraypush(array, "char");
	array = arraypush(array, "double");
	
	array = arraypush(array, "double const");
	array = arraypush(array, "float const");
	array = arraypush(array, "char const");
	array = arraypush(array, "char signed");
	array = arraypush(array, "char signed const");
	array = arraypush(array, "short const");
	array = arraypush(array, "short");
	array = arraypush(array, "unsigned char");
	
	array = arraypush(array, "unsigned char const");
	array = arraypush(array, "int short");
	array = arraypush(array, "int short const");
	array = arraypush(array, "unsigned int");
	array = arraypush(array, "unsigned int const");
	array = arraypush(array, "long int");
	
	array = arraypush(array, "long int const");
	array = arraypush(array, "long long int");
	array = arraypush(array, "long long int const");
	array = arraypush(array, "unsigned long int");
	
	array = arraypush(array, "unsigned long int const");

/*	array = arraypush(array, "unsigned long long");
	array = arraypush(array, "unsigned long long const");
	array - arraypush(array, "unsigned long long int"); */
	return (array);
}

char **arraydelete(char **array, int to_remove)
{
	char **new;
	int i;

	i = 0;
	if (array == NULL)
		return (NULL);
	new = NULL;
	while (array[i])
	{
		if (i == to_remove)
		{
			i++;
			continue ;
		}
		new = arraypush(new, array[i]);
		i++;
	}
	return (new);
}
 
t_token	*skip_distance(t_token *token, char *datatype_len)
{
	char **segments;
	int len;
	int counter;

	segments = split(datatype_len, ' ');
	len = arraylen(segments);
	counter = 0;
	while (counter < len - 1 && token)
	{
		token = token->next;
		counter++;
	}
	return (token);
}

char	*valid_datatypes(t_token *token)
{
	char **valid_datatypes;
	char **found;
	int i;
	char **to_check;
	t_token *trav;
	char *to_return;
	extern char **start;
	
	to_return = NULL;
	i = 0;
	found = NULL;
	if (value_found(token->name, start) == false)
		return (NULL);
	valid_datatypes = legal_combinations();
	while (valid_datatypes[i])
	{
		trav = token;
		while (trav && strcmp(trav->type, "KEYWORD") == 0)
		{
			found = arraypush(found, trav->name);
			trav = trav->next;
		}
		to_check = split(valid_datatypes[i], ' ');
		int j = 0;
		int flag = -1;
		while (to_check[j])
		{
			int k = 0;
			while (found[k])
			{
				if (strcmp(found[k], to_check[j]) == 0)
				{
					found = arraydelete(found, k);
					k = 0;
					if (found == NULL)
					{
						flag = 1;
						break;
					}
				}	
				k++;
			}
			if (flag == 1)
				break;
			j++;
		}
		if (found == NULL)
		{
			to_return = strdup(valid_datatypes[i]);
			break ;
		}
		else
			found = NULL;
		i++;
	}
	token = trav;
	if (to_return)
		token = skip_distance(token, to_return);
	free2d(valid_datatypes);	
	return (to_return);
}


