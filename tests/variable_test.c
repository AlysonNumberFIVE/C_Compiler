
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../inc/symbol.h"
#include "../inc/token.h"
#include "../inc/compiler.h"

/*
typedef struct  s_symbols
{
    char                *name;
    char                *datatype;
    short               size;
    struct s_symbols    **array;
    size_t              array_size;
    uint32_t            decl_line;
    uint32_t            usage_line;
    t_hashtable         *value;
    struct s_symbols    *next;
}t_symbol;
*/

/*
t_symbol    *push_variable(t_symbol *first, char *name,
                char *datatype, short size,
                char *key, char *value,
                size_t table_size,
                size_t array_size,
                uint32_t decl_line,
                uint32_t usage_line)
*/

// test bed


t_token    *lex(char *buffer)
{
    t_token         *token;
    t_token        *list;
    extern size_t   read_count;
    size_t          size;
    t_hashtable *table;

    table = key_token();
    list = NULL;
    size = strlen(buffer);
    read_count = 0; 
    while (read_count < size)
    {
        token = scan(buffer, table);
        if (token)
            list = push_token(list, token->name, token->type);;
    }
    return (list);
}


t_symbol    *read_variable(void)
{
    extern size_t   read_count;
    t_token         *list;
    t_token         
    char            *datatype = NULL;
    char            *var_name = NULL;
    short           data_size = 0;
    char            *value = NULL;
    int             heap_or_stack = -1
    int             array_size = 0;


    list = lex("char *buffer = \"Hello World\"");

    return (NULL);
}

int main(void)
{
    char *file = "char c = 'c';";
    t_symbol    *vars;

    vars = NULL;
//    vars = push_variable(vars, "variable", "char", 1, "variable", "c", 
//                        STACK,  0, 4, 8);
    read_variable();
    return (0);
}
