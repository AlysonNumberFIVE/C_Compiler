


#include "../inc/compiler.h"
#include "../inc/token.h"




void    semantic_if(t_token *token)
{
   t_token *list;
   
   if (strcmp(token->name, "(") != 0)
       return ;

   list = token->next;
   while (list)
   {
        
   }
}

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
    semantic_if(list);
    return (0);
}

