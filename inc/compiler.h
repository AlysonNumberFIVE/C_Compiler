
#ifndef COMPILER_H
#define COMPILER_H

#include "../alylibc/inc/lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// datatype values

#define CHAR            0
#define UNSIGNED_CHAR   1
#define SIGNED_CHAR     2
#define INT             3
#define UNSIGNED_INT    4
#define SHORT           5
#define UNSIGNED_SHORT  6
#define LONG            7
#define UNSIGNED_LONG   8
#define FLOAT           9
#define DOUBLE          10
#define LONG_DOUBLE     11
#define VOID            12

#define DEFINE          1
#define TYPEDEF         2
#define CAPACITY        500000

#define STACK           1
#define HEAP            2

#define ARRAY		1
#define SCOPE		2
// hashtable

typedef struct ht_item
{
    char *key;
    char *value;
    struct ht_item *next;
}   ht_item;


typedef struct Hashtable {
    ht_item     **items;
    int         size;
    int         count;
}   t_hashtable;

typedef struct s_datatype
{
    char *name;
    int size;
    struct s_datatype   *next;
}   t_datatype;

//struct s_datatype datatypes[13];

static char hashes[5][10] = {
    "#include\0", "#define\0", "#ifndef\0", "#define\0", "#endif\0"
};
/*
static char first_order[4][9] = {
    "unsigned\0",
    "static\0",
    "extern\0",
    "typedef\0"
};


static char primitives[33][9] = {
    "char\0",
    "const\0",
    "void\0",
    "struct\0",
    "int\0",
    "short\0",
    "double\0",
    "float\0",
    "size_t\0",
    "long\0",
    "signed\0",
    "void\0",
};
*/
static char reserved[33][9] = {
    "auto\0",     "break\0",    "case\0",     "char\0", 
    "const\0",    "continue\0", "default\0",  "do\0",
    "int\0",      "long\0",     "register\0", "return\0",
    "short\0",    "signed\0",   "sizeof\0",   "static\0",
    "struct\0",   "switch\0",   "typedef\0",  "union\0",
    "unsigned\0", "void\0",     "volatile\0", "while\0",
    "double\0",   "else\0",     "enum\0",     "extern\0",
    "float\0",     "for\0",     "gaoto\0",     "if\0",
    "size_t\0"
};
/*
typedef struct  s_variable
{
    char    *name;
    char    *datatype;
    char    *value;
    struct s_variable   *next;
}   t_variable; */


typedef struct  s_scope
{
    int depth;
    struct s_scope *next;
    struct s_cope *prev;
    //t_variable *variables;
}   t_scope;

// function info

typedef struct  s_function_table
{
    char *function_name;
    char *datatype;
    //t_variable *variables;
    bool is_defined; 
    struct s_function_table *next;
}   t_function_table;

// alias info   

typedef struct  s_preproc
{
    char    *define;
    char    *value;
    struct s_preproc *next;
}   t_preproc;

typedef struct  s_alias
{
    char    *name;
    char    *value;
    bool    is_typedef;
    bool    is_define;
    struct s_alias  *next;
}   t_alias;

typedef struct  token {
    char        *name;
    char        *type;
    int         line;
    char        *filename;
    struct token    *next;
}   t_token;


typedef struct	s_files
{
	char 		**content;
	char		*filename;
	char		*solidcontent;
	struct s_files	*next;
}	t_file;
/*
typedef struct  s_amcro_env {
    char *name;
    struct s_macro_env *next;
}   t_macro;

typedef struct  s_stack {
    char *funct_name;
    struct s_stack  *next;
    struct s_stack  *prev;
}   t_stack; */

// semantic analysis 

typedef struct s_variable_block
{
        char *name;
        char *type;
        t_token *curr;
        int depth;
}       t_temp_var;

void		print_x(t_token *token, int x);
t_temp_var      *create_temp_var(t_token *token);
void        init_datatypes(void);
t_hashtable *create_table(int size);
char        *ht_search(t_hashtable *table, char *key);
void        ht_insert(t_hashtable *table, char *key, char *value);
char        *file_content(char *filename);
char        *join_files(char *all_files, char *current_file);
char        *read_file(char *filename);
void        print_table(t_hashtable *table);
int         eval_expr_is_legal(char **tokens);
int         eval_expr_is_legal(char **tokens);
void        print_scope(t_scope *scope);
//void        print_variables(t_variable *variables);
void        print_function(t_function_table *functions);
t_hashtable *first_and_follow(void);
bool        validate_id(char *str);
int	    handle_native_csg(char *prev, char *current);
t_file	    *push_file(t_file *head, char *filename, char *file_content);
bool        value_found(char *s, char **str);
t_token	    *error_recover(t_token *token, char *message, t_token *current);
t_token	    *forward_recovery(t_token *token, char *message, t_token *current);
t_token	    *panic_mode(t_token *trav, t_token *back, int brackets);
t_token	    *error_mode(t_token *token, char *message);
int	    type_length(t_token *token);
void	    free_tokens(t_token *token);
void	    print_token(t_token *token);
void	    print_linear(t_token *token);

#endif

