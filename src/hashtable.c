
#include "../inc/compiler.h"

void    print_table(t_hashtable *table)
{
    int i;

    i = 0;
    while (i < table->size)
    {
        if (table->items[i])
        {
            printf("inde : %d key : %s - value %s\n", i, table->items[i]->key,table->items[i]->value);
            if (table->items[i]->next)
            {
                ht_item *trav = table->items[i]->next;
                while (trav)
                {
                    printf("\t%s\n", trav->value);
                    trav = trav->next;
                }
            }
        }
        i++;
    }
}


ht_item *create_item(char *key, char *value)
{
    ht_item     *item;

    item = (ht_item *)malloc(sizeof(ht_item));
    item->key = strdup(key);
    item->value = strdup(value);
    item->next = NULL;
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

ht_item   *handle_collision(ht_item *current_time, char *key, char *value)
{
    current_time->next = (ht_item *)malloc(sizeof(ht_item));
    current_time->next->key = strdup(key);
    current_time->next->value = strdup(value);
    current_time->next->next = NULL;
    return (current_time);
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
        else
            table->items[index] = handle_collision(table->items[index], key, value);    
    }
}

char    *searching_collision_field(ht_item *item, char *key)
{
    ht_item *trav;

    trav = item;
    while (trav)
    {
        if (strcmp(trav->key, key) == 0)
            return (trav->value);
        trav = trav->next;
    }
    return (NULL);
}

char    *ht_search(t_hashtable *table, char *key)
{
    int index;
    ht_item *item;

    index = hash_function(key);
    item = table->items[index];
    if (item)
    {
        if (item->next)
        {
            return (searching_collision_field(item, key));
        }
        if (strcmp(item->key, key) == 0)
            return (item->value);
    }
    return (NULL);
}
/*
int main(void)
{
    t_hashtable    *ht = create_table(CAPACITY);
    ht_insert(ht, ">>=", "First address");
    ht_insert(ht, "|=", "Second address");
    
    char *first = ht_search(ht, "|=");
    char *second = ht_search(ht, ">>=");
    printf("first is %s\n",first);
    printf("second is %s\n", second);
    return (0);
}
*/

