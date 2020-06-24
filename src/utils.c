
#include <unistd.h>
#include <fcntl.h>
#include "../inc/compiler.h"
#include <sys/stat.h>

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
