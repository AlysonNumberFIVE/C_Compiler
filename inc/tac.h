

#ifndef TAC_H
#define TAC_H

#include "compiler.h"
#include "intermediate.h"

typedef struct  token_depth
{
        char    *type;
        int     depth;
        struct token_depth *next;
}       t_td;

typedef struct	s_blocks
{
	char	*block;
	int	label;
	int 	togo;
	int	depth;
	t_code	*assembly;
	struct s_blocks *next;
	struct s_blocks *prev;
}	t_block;

typedef struct  s_tree
{
        char *type;
        t_token *tokens;
	int scope;
        struct s_tree *next;
}       t_tree;

t_block	*push_block(t_block *head, char *block, int label, int togo, int depth);\
t_block	*patch_elseif(t_block *block);
void	print_blocks(t_block *block);
t_tree	*push_tree(t_tree *head, char *type, t_token *tokens, int scope);
char 	*get_syntactic_name(t_token *token);
void	create_tac_structure(t_tree *ast);
bool	three_address_code(char **str);
void	print_asm(t_code *assembly);
t_td	*push_td(t_td *head, char *name, int type);
void	print_tac(t_block *blocks);

#endif
