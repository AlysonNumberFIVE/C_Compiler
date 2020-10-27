

#include "../inc/compiler.h"

t_hashtable *store = NULL;

t_hashtable *init_typedef_store(void)
{
	t_hashtable *typedef_store;

	typedef_store = create_table(1000);
	return (typedef_store);
}

void	add_typedef_value(char *key, char *value)
{
	ht_insert(store, key, value);
} 

char	*get_typedef_value(char *key)
{
	return (strdup(ht_search(store, key)));
}


