



#include <limits.h>
#include "../inc/typing.h"
#include "../inc/compiler.h"
#include "../inc/semantic.h"


t_typecast	*is_typecast_value(t_token *token)
{
	t_token	*trav;
	int	brackets;
	bool	in_brackets;
	extern char **start;
	t_typecast *current_type;

	current_type = (t_typecast *)malloc(sizeof(t_typecast));
	current_type->datatype = NULL;
	current_type->depth = 0;
	in_brackets = false;
	brackets = 0;
	trav = token;
	if (strcmp(trav->name, "(") != 0)
		return (NULL);
	trav = trav->next;
	if (!value_found(trav->name, start))
		return (NULL);
	
	current_type->datatype = strdup(trav->name);
	trav = trav->next;
	while (trav && strcmp(trav->name, "*") != 0)
	{
		current_type->depth++;
		trav = trav->next;
	}
	if (strcmp(trav->name, ")") != 0)
		return (NULL);
	return (current_type);
}

// { "datatye" : "size min_size max_size


char		*save_datatype_sizes(int width, long long int min, long long int max)
{
	char *value;

	value = (char *)malloc(sizeof(char) * 50);
	bzero(value, 50);
	snprintf(value,	50, "%d %lld %lld", width, min, max);
	return (value);
}

t_hashtable	*type_size_list(void)
{
	t_hashtable	*typelist;

	typelist = create_table(500);
	ht_insert(typelist, "char short", save_datatype_sizes(sizeof(char), -1, CHAR_BIT));
	ht_insert(typelist, "char signed", save_datatype_sizes(sizeof(signed char), SCHAR_MIN, SCHAR_MAX));
	ht_insert(typelist, "unsigned char", save_datatype_sizes(sizeof(char unsigned), -1, UCHAR_MAX));
	ht_insert(typelist, "char", save_datatype_sizes(sizeof(char), CHAR_MIN, CHAR_MAX));
	ht_insert(typelist, "int short", save_datatype_sizes(sizeof(int short), SHRT_MIN, SHRT_MAX));
	ht_insert(typelist, "unsigned short int", save_datatype_sizes(sizeof(unsigned short int), -1, USHRT_MAX));
	ht_insert(typelist, "int", save_datatype_sizes(sizeof(int), INT_MIN, INT_MAX));
	ht_insert(typelist, "unsigned int", save_datatype_sizes(sizeof(unsigned int), -1, UINT_MAX));
	ht_insert(typelist, "long int", save_datatype_sizes(sizeof(long int), LONG_MIN, LONG_MAX));
	ht_insert(typelist, "unsigned long int", save_datatype_sizes(sizeof(unsigned long int), -1, ULONG_MAX));
	return (typelist);
}






























