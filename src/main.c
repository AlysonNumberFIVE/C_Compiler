
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../inc/compiler.h"
#include "../inc/semantic.h"
#include "../inc/token.h"

char    *test_file(char *filename)
{
    int fd;
    struct stat info;
    char *content;

    fd = open(filename, O_RDONLY);
    fstat(fd, &info);
    content = (char *)malloc(sizeof(char) * info.st_size + 1);
    read(fd, content, info.st_size);
    content[info.st_size] = '\0';
    close(fd);
    return (content);
}

void    print_token(t_token *token)
{
    t_token *trav;
    printf("here\n");
    trav = token;
    while (trav)
    {
        printf("%s : %s\n", trav->name, trav->type);
        trav = trav->next;
    }
}


int	main(int argc, char **argv)
{
	char *file;
	t_token *tokens;

	if (argc != 2)
	{
		printf("Usage: %s [c_file] - only 1 file is supported\n", argv[0]);
		return (1);
	}
	file = test_file(argv[1]);

	printf("%s\n", file);

	tokens = lexer(file);
	semantic_analysis(tokens);
	
	return (0);	
}
