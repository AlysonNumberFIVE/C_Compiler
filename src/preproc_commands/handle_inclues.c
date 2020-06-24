

#include "../../inc/preprocessor.h"
#include <unistd.h>
#include "../../inc/compiler.h"

char    *create_path(char *path, char *filename, char *c_file)
{
    char *newpath;
    char *temp;
    
    if (strchr(c_file, '/')) 
    {
        size_t  file_len = strlen(c_file) - 1;
        char    *to_ret;

        while (c_file[file_len] != '/')
            file_len--;
        newpath = strndup(c_file, file_len);
        temp = join(path, "/");
        to_ret = join(temp, newpath);
        free(newpath);
        free(temp);
        temp = strdup(to_ret);
        free(to_ret);
       temp = join(temp, "/"); 
        //   return (to_ret);
    }
    else
     temp = join(path, "/");
    newpath = join(temp, filename);
    free(temp);
    return (newpath);
}


static char    *handle_system_lib(char *lib_name)
{
    char        *system_path;
    char        *filename;
    char        *abspath;
    char        *content;
    
    filename = sub(lib_name, 1, strlen(lib_name) - 2);
    system_path = strdup("/Library/Developer/CommandLineTools/usr/include/c++/v1/");
    abspath = join(system_path, filename);
    content = file_content(abspath);
    free(abspath);
    free(filename);
    free(system_path);
    return (content);
}

static char    *handle_local_lib(char *lib_name, char *filename)
{
    char    directory[1024];
    char    *abspath;
    char    *segname;
    char    *content;
    
    segname = sub(lib_name, 1, strlen(lib_name) - 2);
    bzero(directory, 1024);
    getcwd(directory, 1024);
    abspath = create_path(directory, segname, filename);
    printf("abspath is %s\n", abspath);
    content = file_content(abspath);
    return (content);
}


//size_t      skip_whitespace(char *buffer, size_t start, size_t length);

char  *handle_include(char *content, size_t size, char *filename)
{
    char    *lib_name;
    size_t  filesize;
    char    *segment;
    extern size_t end;

    segment = NULL;
    filesize = strlen(content);
    lib_name = NULL;
    size++;
    size = skip_whitespace(content, size, strlen(content));
    do 
    {
        lib_name = charpush(lib_name, content[size]);
        size++;
    }
    while (content[size] != ' ' && content[size] != '\t' &&
          content[size] != '\n' && size < filesize);
    while (content[size] != '\n')
    {
        if (content[size]  != '\t' || content[size] != ' ')
            return (NULL);
        size++;
    }
    end = size;
    if (startswith(lib_name, '<') == 1 && endswith(lib_name, '>') == 1)
    {
         segment = handle_system_lib(lib_name);
         free(lib_name);
    }

    else if (startswith(lib_name,'"') == 1 && endswith(lib_name, '"') == 1)
    {
        segment = handle_local_lib(lib_name, filename);
        free(lib_name);
    } 
    return (segment);
}
