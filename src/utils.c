/*
#include <unistd.h>
#include <fcntl.h>
#include "../inc/compiler.h"
#include <time.h>
#include <sys/stat.h>
*/
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

long arraylen(char **array)
{
    long  i;

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
            return (false);
        count++;
    }
    if (bracket_depth != 0)
        return (false);
    return (0);
}

int     character_to_int(char *value)
{
    char    *chr;
    char    *psh;
    char    *nbr;

    chr = sub(value, 1, strlen(value) - 2);
    if (chr[0] == '\\')
        psh = &chr[1];
    nbr = itoa(psh[0] - '0');
    free(value);
    free(chr);
    return (nbr);
}

char    *evaluate_variable(t_scope *scope, char *var_name)
{
    t_variable *var_list;
    char        *value;

    value = NULL;
    if (is_symbol(var_name) == true)
        return (strdup(var_name));
    var_list = scope->variables;
    while (var_list)
    {
        if (strcmp(var_name, var_list->name) == 0)
        {
            value = strdup(var_list->value);
            break ;
        }
        var_list = var_list->next;
    }
    if (value)
    {
        srand(time(0));
        if (value[0] == '\"' || value[0] == '[')
        {
            free(value);
            value = strdup(itoa(rand()));
        }
        else if (value[0] == '\'')
            value = character_to_int(value);
    }
    return (value);
}

bool    evaluate_expression(t_token *tokens, t_scope *scope)
{
    char    **array;
    char    *tmp;
    int     eval;

    array = NULL;
    while (tokens->next && (strcmp(tokens->name, ")") != 0 && strcmp(tokens->next->name, "{") != 0))
    {
        if (strcmp(tokens->type, "NUM") != 0)
        {
            tmp = evaluate_variable(scope, tokens->name);
            array = arraypush(array, tmp);
            free(tmp);
        }
        else
            array = arraypush(array, tokens->name);
        tokens = tokens->next;
    }
    eval = eval_expr_is_legal(array);
    
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
