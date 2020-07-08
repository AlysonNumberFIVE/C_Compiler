


#ifndef _SEMANTIC_
#define _SEMANTIC_

#include "compiler.h"

char    *datatype_name(char *name, char *to_add);
bool    assert_second_order(char *to_check);
bool    assert_first_order(char *to_check);
int     determine_pointer_depth(t_token *list);
//int     semantic_function(t_token *tokens);
t_stack *pop_stack(t_stack *top);
t_stack *push_stack(t_stack *head, char *function_name);
int     semantic_function(t_token **tokens);

#endif
