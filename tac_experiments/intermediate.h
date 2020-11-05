

#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct  s_intermediate
{
        int line_number;
        char *line;
        struct s_intermediate *next;
        struct s_intermediate *prev;
}       t_code;
t_code	*push_line(t_code *head, int line_number, char *line);


#endif
