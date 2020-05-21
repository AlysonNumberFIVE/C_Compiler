
size_t  read_count = 0;
size_t  line = 0;

void    _(char *str)
{
    printf("%s\n", str);
}

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
