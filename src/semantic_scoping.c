


#include "../inc/compiler.h"
#include "../inc/token.h"



int     main(int argc, char **argv)
{
    char *file = file_content(argv[1]);
    t_token *list = lexer(file);
    t_token *print;

    print = list;
    while (print)
    {
        printf("%s : %s\n", print->name, print->type);
        print = print->next;
    }
    semantic_scoping(list);
    return (0);
}

