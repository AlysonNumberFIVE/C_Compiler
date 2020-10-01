


#ifndef _DATABASE_H
#define _DATABASE_H
#include "compiler.h"

typedef struct  s_scope_database
{
        char    *type;
        char    *name;
        char    *value;
        struct s_scope_database *next;
}       t_db;
t_hashtable *first_and_follow(void);
t_db    *new_object(char *type, char *name, char *val);
t_db    *add_object(t_db *db, char *type, char *name, char *val);
t_db    *push_object(t_db *db, char *type, char *name, char *val);
void    free_db(t_db *db);
void    insert_into_db(char *type, char *name, char *val);
char    *get_from_db(char *variable);
void    drop_last_table(void);
void    add_new_table(void);



#endif
