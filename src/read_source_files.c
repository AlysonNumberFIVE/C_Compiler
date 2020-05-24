#include <ctype.h>
#include "../inc/token.h"
#include "../inc/compiler.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


char    *read_file(char *filename)
{
    int         fd;
    struct stat info;
    size_t      size;
    char        *content;

    fd = open(filename, O_RDONLY);
    fstat(fd, &info);
    size = info.st_size;
    content = (char *)malloc(sizeof(char) * size + 1);
    read(fd, content, size);
    content[size] = '\0';
    close(fd);
    return (content);
}

char    *join_files(char *all_files, char *current_file)
{
    char    *tmp;

    tmp = join(all_files, current_file);
    free(all_files);
    all_files = strdup(tmp);
    free(tmp);
    return (all_files);
}

char    *file_content(int argc, char **argv)
{
    int     counter;
    char    *all_files;
    char    *current_file;

    all_files = (char *)malloc(sizeof(char));
    counter = 1;
    while (counter < argc)
    {
        current_file = read_file(argv[counter]);
        all_files = join_files(all_files, current_file);
        counter++;
    }
    return (all_files);
 }
