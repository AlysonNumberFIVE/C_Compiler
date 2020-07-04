

#ifndef FIRST_AND_FOLLOW
#define FIRST_AND_FOLLOW_

// first and follow for variable declaration.

typedef struct  s_beta_datatype
{
    struct s_fdatatype *datatype;
}   t_fdatatype;

typedef struct  s_fdatatype
{
    char    **datatypes;
    struct s_id *next;
}   t_fdatatype;

typedef struct  s_id 
{
    struct s_openbrace  *openbrace;
    struct s_assign     *assign;
    struct s_colon      *colon;
}   t_id;

typedef struct  s_openbrace
{
    struct s_d_list   *d_list;
}   t_openbrace;

typedef struct  s_d_list
{
    struct s_closebrace *closebrace;
}   t_d_list;

typedef struct s_closebrace
{
    struct s_colon  *colon;
    struct s_openbracket *openbracket;
}   t_closebrace;

typedef struct s_assign
{
    struct s_values *values;
}   t_assign;

typedef struct  s_value
{
    struct s_colon *colon;
}   t_value;

typedef struct s_colon
{
    void    *null;
}   t_colon;





#endif
