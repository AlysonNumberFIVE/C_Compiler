
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../inc/compiler.h"
#include "../inc/semantic.h"
#include "../inc/token.h"

char    *read_file(char *filename)
{
    int fd;
    struct stat info;
    char *content;

    fd = open(filename, O_RDONLY);
    fstat(fd, &info);
    content = (char *)malloc(sizeof(char) * info.st_size + 1);
    read(fd, content, info.st_size);
    content[info.st_size - 1] = '\0';
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

t_file	*get_files(int argc, char **argv)
{
	int	i;
	t_file	*files;
	char 	*content;

	files = NULL;
	i = 1;
	while (i < argc)
	{
		content = read_file(argv[i]);
		files = push_file(
			files,
			argv[i],
			content
		);
		free(content);
		i++;
	}
	return (files);
}

void	print_files(t_file *files)
{
	t_file	*trav;

	trav = files->next;
	while (trav)
	{
		printf("name : %s\n", trav->filename);
		int i = 0;
		while (trav->content[i])
		{
			printf("line %d %s", i + 1, trav->content[i]);
			i++;
		}
		if (trav->next == NULL)
			printf("NULL\n");
		trav = trav->next;
	}
}

int	main(int argc, char **argv)
{
	t_file *files;
	t_token *tokens;

	if (argc < 2)
	{
		printf("Usage: %s [c_file] - only 1 file is supported\n", argv[0]);
		return (1);
	}
	files = get_files(argc, argv);
	print_files(files);
//	printf("%s\n", file);

//	tokens = lexer(file);
//	semantic_analysis(tokens);
	
	return (0);	
}
