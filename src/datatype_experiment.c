

#include "../inc/compiler.h"
#include "../inc/semantic.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "../inc/token.h"

t_file  *files = NULL;

char    *read_file(char *filename)
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
    trav = token;
    while (trav)
    {
        printf("line: %u %s : %s\n", trav->line, trav->name, trav->type);
        trav = trav->next;
    }
}

t_file  *get_files(int argc, char **argv)
{
        int     i;
        t_file  *files;
        char    *content;

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



char 	**legal_combinations(void)
{
	char **array;

	array = NULL;

	array = arraypush(array, "int");
	array = arraypush(array, "long");
	array = arraypush(array, "void");
	array = arraypush(array, "float");
	array = arraypush(array, "size_t");
	array = arraypush(array, "char");
	array = arraypush(array, "double");
	
	array = arraypush(array, "double const");
	array = arraypush(array, "float const");
	array = arraypush(array, "char const");
	array = arraypush(array, "char signed");
	array = arraypush(array, "char signed const");
	array = arraypush(array, "short const");
	array = arraypush(array, "short");
	array = arraypush(array, "unsigned char");

	array = arraypush(array, "unsigned char const");
	array = arraypush(array, "int short");
	array = arraypush(array, "int short const");
	array = arraypush(array, "unsigned int");
	array = arraypush(array, "unsigned int const");
	array = arraypush(array, "long int");
	
	array = arraypush(array, "long int const");
	array = arraypush(array, "long long int");
	array = arraypush(array, "long long int const");
	array = arraypush(array, "unsigned long int");
	
	array = arraypush(array, "unsigned long int const");

/*	array = arraypush(array, "unsigned long long");
	array = arraypush(array, "unsigned long long const");
	array - arraypush(array, "unsigned long long int"); */
	return (array);
}

char **arraydelete(char **array, int to_remove)
{
	char **new;
	int i;

	i = 0;
	if (array == NULL)
		return (NULL);
	new = NULL;
	while (array[i])
	{
		if (i == to_remove)
		{
			i++;
			continue ;
		}
		new = arraypush(new, array[i]);
		i++;
	}
	return (new);
}
 
t_token	*valid_datatypes(t_token *token)
{
	char **valid_datatypes;
	char **found;
	int i;
	char **to_check;
	t_token *trav;

	i = 0;
	found = NULL;
	valid_datatypes = legal_combinations();
	printf("again\n");
	while (valid_datatypes[i])
	{
		trav = token;
		while (trav && strcmp(trav->type, "KEYWORD") == 0)
		{
			found = arraypush(found, trav->name);
			trav = trav->next;
		}
		to_check = split(valid_datatypes[i], ' ');
		printf("line is %s\n", valid_datatypes[i]);
		int j = 0;
		printf("NEW LOOP\n");
		int flag = -1;
		while (to_check[j])
		{
			int k = 0;
			while (found[k])
			{
				if (strcmp(found[k], to_check[j]) == 0)
				{
					printf("found %s to_check %s\n", found[k], to_check[j]);

					found = arraydelete(found, k);
					k = 0;
					if (found == NULL)
					{
						printf("found is NULL\n");
						break;
					}
				}	
				k++;
			}
			if (flag == 1)
				break;
			j++;
		}
		if (found == NULL)
		{
			printf("VALID\n");
			break ;
		}
		else
		{
			printf("invalid\n");
			found = NULL;
		}
		i++;
	}
	free2d(valid_datatypes);
	token = trav;
	return (token);
}


int 	main(int argc, char **argv)
{
	t_token *token;

	files = get_files(argc, argv);
	token = lexer(files);
	valid_datatypes(token);
	return (0);
}




