#include <ctype.h>
#include "../inc/token.h"
#include "../inc/compiler.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


t_token     *ellipse_found(char *buffer, size_t index, char *real_name)
{
    char            *var_name;
    extern size_t   read_count;
    size_t          count;
    char            *name;
    t_token         *token;

    count = 0;
    var_name = NULL;
    var_name = charpush(var_name, buffer[index]);
    index++;
    name = real_name;
    if (buffer[index] == '.' && buffer[index + 1] == '.')
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
        var_name = charpush(var_name, buffer[index]);
        index++;
        name = "ELLIPSE";
    }
    read_count = index;
    token = new_token(var_name, name);
    free(var_name);
    return (token);
}

t_token     *number_found(char *buffer, size_t index)
{
    char    *var_name;
    bool    is_float;
    extern size_t read_count;

    is_float = false;
    var_name = NULL;
    do
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
        if (buffer[index] == '.')
        {
            is_float = true;
            index++;
        }
    }
    while (isdigit(buffer[index]));
    read_count = index;
    if (is_float == true)
        return new_token(var_name, "FLOAT");
    return new_token(var_name, "NUM");
}

t_token     *skip_comments(char *buffer, size_t index)
{
    extern int line;
    extern size_t read_count;

    index++;
    if (buffer[index] == '/')
    {
        do
            index++;
        while (buffer[index] != '\n');
        line++;
    }
    else if (buffer[index] == '*')
    {
        do
        {
            index++;
            if (buffer[index] == '*')
            {
                index++;
                if (buffer[index] == '/')
                {
                    index++;
                    break ;
                }
            }
            else if (buffer[index] == '\n')
                line++;
        } while (42);
    }
    read_count = index;
    return (NULL);
}

t_token     *literal_found(char *buffer, size_t index)
{
    char    *var_name;
    t_token *token;
    extern size_t read_count;

    var_name = NULL;
    do
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
    }
    while (buffer[index] != '\"');
    var_name = charpush(var_name, buffer[index]);
    index++;
    read_count = index;
    token =  new_token(var_name, "LITERAL");
    free(var_name);
    return (token);
}

t_token     *character_found(char *buffer, size_t index)
{
    char    *var_name;
    t_token *token;
    int counter;
    int max;
    extern size_t read_count;

    max = 2;
    counter = 0;
    var_name = NULL;
    do
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
        if (buffer[index] == '\\' && buffer[index + 1] == '\'')
            max = 3;
        counter++;
    }
    while (counter < max);
    var_name = charpush(var_name, buffer[index]);
    index++;
    read_count = index;
    token = new_token(var_name, "CHAR");
    free(var_name);
    return token;
}

static bool macro_phrase(char *to_check)
{
    int counter;
    extern char hashes[5][10];

    counter = 0;
    while (counter < 5)
    {
        if (strcmp(to_check, hashes[counter]) == 0)
            return (true );
        counter++;
    }
    return (false);
}

static bool reserved_word(char *to_check)
{
    int counter;
    extern char reserved[33][9];

    counter = 0;
    while (counter < 32)
    {
        if (strcmp(to_check, reserved[counter]) == 0)
            return (true);
        counter++;
    }
    return (false);
}

t_token     *macro_found(char *buffer, size_t index)
{
    char    *var_name;
    t_token *token;
    extern size_t read_count;

    var_name = NULL;
    do
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
    }
    while (isalnum(buffer[index]) || buffer[index] == '_');
    read_count = index;
    token = new_token(var_name, "MACRO");
    free(var_name);
    return token;
}

t_token     *header_found(char *buffer, size_t index)
{
    char    *var_name;
    t_token *token;
    extern size_t read_count;

    var_name = NULL;
    do
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
    }
    while (buffer[index] != '>');
    index++;
    read_count = index;

    token = new_token(var_name, "HEADER");
    free(var_name);
    return token;
}

t_token     *id_found(char *buffer, size_t index)
{
    char    *var_name;
    t_token *token;
    extern size_t read_count;

    var_name = NULL;
    do
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
    }
    while (isalnum(buffer[index]) || buffer[index] == '_');
    read_count = index;
    if (reserved_word(var_name) == true)
        token = new_token(var_name, "KEYWORD");
    else
        token = new_token(var_name, "ID");
    free(var_name);
    return (token);
}
