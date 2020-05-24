
#ifndef TOKEN_H
#define TOKEN_H

#include "compiler.h"

#define AND     256
#define BREAK   258
#define DO      259
#define ELSE    260
#define EQ      261
#define FALSE   262
#define GE      263
#define ID      264
#define IF      265
#define INDEX   266
#define LE      267
#define MINUS   268
#define NE      269
#define NUM     270
#define OR      271`

t_token *new_token(char *name, char *type);
t_hashtable     *key_token(void);
t_token *push_token(t_token *first, char *name, char *type);
t_token     *scan(char *buffer, t_hashtable *table);

// lexer_utils.c

t_token     *double_token(char *buffer, size_t index, t_hashtable *table, char *first_name);
t_token     *single_token(char *buffer, size_t index, char *tok_name);

// lexer_token_type.c

t_token     *id_found(char *buffer, size_t index);
t_token     *number_found(char *buffer, size_t index);
t_token     *skip_comments(char *buffer, size_t index);
t_token     *literal_found(char *buffer, size_t index);
t_token     *character_found(char *buffer, size_t index);
t_token     *macro_found(char *buffer, size_t index);
t_token     *header_found(char *buffer, size_t index);

#endif
