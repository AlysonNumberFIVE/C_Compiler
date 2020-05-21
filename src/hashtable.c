
#include "../inc/compiler.h"


ht_item *create_item(char *key, char *value)
{
    ht_item     *item;

    item = (ht_item *)malloc(sizeof(ht_item));
    item->key = strdup(key);
    item->value = strdup(value);
    return (item);
}

t_hashtable *create_table(int size)
{
    t_hashtable *table;
    int         i;

    table = (t_hashtable *)malloc(sizeof(t_hashtable));
    table->size = size;
    table->count = 0;
    table->items = (ht_item **)calloc(table->size, sizeof(ht_item*));
    for (i = 0; i < table->size; i++)
        table->items[i] = NULL;
    return (table);
}

void    free_item(ht_item *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

unsigned long long hash_function(char *str)
{
    unsigned long i;
    int           j;
    
    i = 0;
    for (j = 0; str[j]; j++)
    {
        i += str[j];
    }
    return i % CAPACITY;
}

void    free_table(t_hashtable *table)
{
    int i;
    ht_item *item;

    for (i = 0; i < table->size; i++)
    {
        item = table->items[i];
        if (item)
            free_item(item);
    }
    free(table->items);
    free(table);
}

void    ht_insert(t_hashtable *table, char *key, char *value)
{
    ht_item *current_item;
    ht_item *item;
    int      index;

    item = create_item(key, value);
    index = hash_function(key);
    current_item = table->items[index];
    if (current_item == NULL)
    {
        if (table->count == table->size)
        {
            free_item(item);
            return ;
        }
        table->items[index] = item;
        table->count++;
    }
    else
    {
        if (strcmp(current_item->key, key) == 0)
        {
            free(table->items[index]->value);
            table->items[index]->value = strdup(value);
            return ;
        }
        // else collisiion
    }
}

char    *ht_search(t_hashtable *table, char *key)
{
    int index;
    ht_item *item;

    index = hash_function(key);
    item = table->items[index];
    if (item)
    {
        if (strcmp(item->key, key) == 0)
            return (item->value);
    }
    return (NULL);
}
/*
int main(void)
{
    t_hashtable    *ht = create_table(CAPACITY);
    ht_insert(ht, "1", "First address");
    ht_insert(ht, "2", "Second address");
    char *first = ht_search(ht, "1");
    char *second = ht_search(ht, "2");
    printf("first is %s\n",first);
    printf("second is %s\n", second);
    return (0);
}*/






