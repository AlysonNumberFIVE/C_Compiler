
#include <unistd.h>
#include <fcntl.h>
#include "../inc/compiler.h"
#include <sys/stat.h>

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

char    evaluate_variable(t_scope *scope, char *var_name)
{
    t_variable *var_list;
    if (is_symbol(var_name) == true)
        return (strdup(var_name));
    var_list = scope->variables;
    while (var_list)
    {
        if (strcmp(var_name, var_list->name) == 0)
        {
            
        }
    }
}

void    evaluate_expression(t_token *tokens, t_scope *scope)
{
    char    **array;

    array = NULL;
    while (strcmp(tokens->name, ")") != 0 && tokens)
    {
        array = arraypush(array, tokens->name);
        tokens = tokens->next;
    }

}


char    *file_content(char *filename)
{
    int     fd;
    struct stat info;
    char    *content;
    size_t  size;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    fstat(fd, &info);
    size = info.st_size;
    content = (char *)malloc(sizeof(char) * size + 1);
    read(fd, content, size);
    content[size] = '\0';
    return (content);
}
