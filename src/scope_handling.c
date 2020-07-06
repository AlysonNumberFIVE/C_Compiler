

#include "../inc/compiler.h"


t_scope     *create_scope(t_token *tokens)
{
    g_symbol_table = push_scope(NULL);
    return g_symbol_table;
}
