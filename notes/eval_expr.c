

#include "../alylibc/inc/lib.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char labels[5][2] = {"*\0", "/\0", "^\0", "+\0", "-\0"};

/*
 *  (
 *  )
 *  ^
 *  /
 *  *
 *  +
 *  -
 */


void    free_bracket(char **token)
{
    int i;

    i = 0;
    while (token[i])
    {
        free(token[i]);
        i++;
    }
    free(token);
}

size_t  arraylen(char **array)
{
    size_t  i;

    i = 0;
    while (array[i])
        i++;
    return (i);
}

void    print_array(char **array)
{
    int i;
    
    i = 0;
    while (array[i])
    {
        printf("%s ", array[i]);
        i++;;
    }
    printf("\n");
}

bool    is_symbol(char *str)
{
    int     count;

    count = 0;
    while (count < 5)
    {
        if (strcmp(str, labels[count]) == 0)
            return (true);
        count++;
    }
    return (false);
}

void    error_and_exit(void)
{
    printf("ERROR\n");
    exit(1);
}

int     eval_expr_is_legal(char **tokens)
{
    bool    sym;
    int     count;
    size_t  bracket_depth;
    
    sym = false;
    bracket_depth = 0;
    count = 0;
    while (tokens[count])
    {
        if (strcmp(tokens[count], "(") == 0)
        {
            sym = false;
            bracket_depth++;
        }
        else if (strcmp(tokens[count], ")") == 0)
            bracket_depth--;
        else if (is_symbol(tokens[count]) == true)
            sym = true;
        else if (sym == false && !atoi(tokens[count]))
            error_and_exit();
        count++;
    }
    if (bracket_depth != 0)
        error_and_exit();
    return (0);
}


int     main(int argc, char **argv)
{
    char **tokens = split("1 + 2 * 3 * ( 42 / 10 + ( 84^2 * 99 + ( 88 + 421 * ( 42 + 1 ) ) + 22 ) ) + ( 11 / 42 )", ' ');
    eval_expr_is_legal(tokens);
    printf("SUCCESS\n");
    return (0);
}




