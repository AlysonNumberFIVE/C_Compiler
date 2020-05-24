


#include <unistd.h>
#include "../inc/token.h"
#include "../inc/compiler.h"
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

void    error_and_exit(char *str)
{
    printf("%s\n", str);
    exit(1);
}

char    *read_file(char *filename)
{
    char            *content;
    size_t          size;
    struct stat     info;
    int             fd;

    fd = open(filename, O_RDONLY);
    fstat(fd, &info);
    size = info.st_size;
    content = (char *)malloc(sizeof(char) * size + 1);
    read(fd, content, size);
    content[size] = '\0';
    close(fd);
    return content;
}

t_token  *get_tokens(char *buffer)
{
    t_hashtable *table;
    extern size_t   read_count;

    table = key_token();
    t_token *list = NULL;
    size_t size = strlen(buffer);
    while (read_count < size)
    {
        t_token *temp = scan(buffer, table);
        if (temp)
            list = push_token(list, temp->name, temp->type);
    }
    return (list);
}

void    free_tokens(t_token *list)
{
    t_token *extr;

    while (list)
    {
        extr = list;
        list = list->next;
        free(extr->name);
        free(extr->type);
        free(extr);
    }
}

bool    assert_token(t_token *list, char *value)
{
    t_token *trav;

    if (list == NULL) printf("NULL\n");
    trav = list;
    while (trav)
    {
        if (strcmp(value, trav->name) == 0)
            return (true);
        printf("Name  : %s\n", trav->name);
        trav = trav->next;
    }
    return (false);
}


bool    test2(t_token *tokens)
{
    if (!assert_token(tokens, ";")) {printf("Failed at ; check\n"); return (false);}
    if (!assert_token(tokens, "{")) {printf("Failed at { check\n"); return (false);}
    if (!assert_token(tokens, "}")) {printf("Failed at } check\n"); return (false);}
    if (!assert_token(tokens, ",")) {printf("Faield at , check\n"); return (false);}
    if (!assert_token(tokens, ":")) {printf("Failed at : check\n"); return (false);}
    if (!assert_token(tokens, "=")) {printf("Failed at = check\n"); return (false);}
    if (!assert_token(tokens, "(")) {printf("Faield at ( check\n"); return (false);}
    if (!assert_token(tokens, ")")) {printf("Failed at ) check\n"); return (false);}
    if (!assert_token(tokens, "[")) {printf("Failed at [ check\n"); return (false);}
    if (!assert_token(tokens, "]")) {printf("Failed at ] check\n"); return (false);}
    if (!assert_token(tokens, ".")) {printf("Failed at . check\n"); return (false);}
    if (!assert_token(tokens, "&")) {printf("Failed at & check\n"); return (false);}
    if (!assert_token(tokens, "!")) {printf("Failed at ! check\n"); return (false);}
    if (!assert_token(tokens, "-")) {printf("Failed at - check\n"); return (false);}
    if (!assert_token(tokens, "~")) {printf("Failed at ~ check\n"); return (false);}
    if (!assert_token(tokens, "+")) {printf("Failed at + check\n"); return (false);}
    if (!assert_token(tokens, "*")) {printf("Failed at * check\n"); return (false);}
    if (!assert_token(tokens, "/")) {printf("Failed at / check\n"); return (false);}
    if (!assert_token(tokens, "%")) {printf("Failed at %% check\n"); return (false);}
    if (!assert_token(tokens, "<")) {printf("Failed at < check\n"); return (false);}
    if (!assert_token(tokens, ">")) {printf("Failed at > check\n"); return (false);}
    if (!assert_token(tokens, "^")) {printf("Failed at ^ check\n"); return (false);}
    if (!assert_token(tokens, "|")) {printf("Failed at | check\n"); return (false);}
    if (!assert_token(tokens, "?")) {printf("Failed at ? check\n"); return (false);}
    return (true);
}

bool    test1(t_token *tokens)
{
    if (!assert_token(tokens, ">>=")) {printf("Failed >>= check\n"); return(false);}
    if (!assert_token(tokens, "<<=")) {printf("Faield <<= check\n"); return (false);}
    if (!assert_token(tokens, "+=")) {printf("Failed += check\n"); return (false);}
    if (!assert_token(tokens, "-=")) {printf("Failed -= check\n"); return (false);}
    if (!assert_token(tokens, "*=")) {printf("Failed *= check\n"); return (false);}
    if (!assert_token(tokens, "/=")) {printf("Failed /= check\n"); return (false);}
    if (!assert_token(tokens, "%=")) {printf("Failed %%= check\n"); return (false);}
    if (!assert_token(tokens, "&=")) {printf("Failed &= check\n"); return (false);}
    if (!assert_token(tokens, "^=")) {printf("Failed ^= check\n"); return (false);}
    if (!assert_token(tokens, "|=")) {printf("Failed |= check\n"); return (false);}
    if (!assert_token(tokens, ">>")) {printf("Failed >> check\n"); return (false);}
    if (!assert_token(tokens, "<<")) {printf("Failed << check\n"); return (false);}
    if (!assert_token(tokens, "++")) {printf("Failed ++ check\n"); return (false);}
    if (!assert_token(tokens, "->")) {printf("Failed -> check\n"); return (false);}
    if (!assert_token(tokens, "&&")) {printf("Failed && check\n"); return (false);}
    if (!assert_token(tokens, "||")) {printf("Failed || check\n"); return (false);}
    if (!assert_token(tokens, "<=")) {printf("Failed <= check\n"); return (false);}
    if (!assert_token(tokens, ">=")) {printf("Failed >= check\n"); return (false);}
    if (!assert_token(tokens, "==")) {printf("Failed == check\n"); return (false);}
    if (!assert_token(tokens, "!=")) {printf("Failed != check\n"); return (false);}
    return (true);
}

void    test1_file(void)
{
    char    *content;
    t_token *tokens;

    content = read_file("lex_test_files/test1.c");
    tokens = get_tokens(content);

    if (test1(tokens) == false)
        error_and_exit("Test 1 failed, exiting..");
    printf("Test 1 Passed\n\n");
    free_tokens(tokens);
    free(content);
}

void    test2_file(void)
{
    char    *content;
    t_token *tokens;
    extern size_t read_count;

    read_count = 0;
    content = read_file("lex_test_files/test2.c");
    tokens = get_tokens(content);

    if (test2(tokens) == false)
        error_and_exit("Test 2 failed, exiting...");
    printf("Test 2 Passed\n\n");
}

int     main(void)
{
    printf("=================== Lexer Unit Testing ===============\n");
    printf("Test 1 : Testing test1.c file\n");
    test1_file();

    printf("Test 2 : Testing test2.c file\n");
    test2_file();

    printf("Test 3 : Testing test3.c file\n");
 
    return (0);
}
