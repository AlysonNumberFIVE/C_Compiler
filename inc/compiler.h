
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

struct s_datatype datatypes[13];

static char hashes[5][10] = {
    "#include\0", "#define\0", "#ifndef\0", "#define\0", "#endif\0"
};

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


typedef struct  s_variable
{
    char    *name;
    char    *datatype;
    char    *value;
    struct s_variable   *next;
}   t_variable;


typedef struct  s_scope
{
    int depth;
    struct s_scope *next;
    struct t_variable *variables;
}   t_scope;

// function info

typedef struct  s_functin_table
{
    char *function_name;
    char *datatype;
    t_variables *variavbles;
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
    struct token    *next;
}   t_token;

typedef struct  s_amcro_env {
    char *name;
    struct s_macro_env *next;
}   t_macro;

// semantic analysis 


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

#endif

