


#ifndef _SEMANTIC_
#define _SEMANTIC_

#include "compiler.h"

char    *datatype_name(char *name, char *to_add);
bool    assert_second_order(char *to_check);
bool    assert_first_order(char *to_check);
int     determine_pointer_depth(t_token *list);
int     semantic_function(t_token *tokens);

#endif
