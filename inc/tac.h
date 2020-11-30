

#ifndef TAC_H
#define TAC_H

#include "compiler.h"
#include "intermediate.h"

typedef struct  s_tree
{
        char *type;
        t_token *tokens;
	int scope;
        struct s_tree *next;
}       t_tree;

t_tree	*push_tree(t_tree *head, char *type, t_token *tokens, int scope);
char 	*get_syntactic_name(t_token *token);
void	create_tac_structure(t_tree *ast);
bool	three_address_code(char **str);
void	print_asm(t_code *assembly);

#endif
