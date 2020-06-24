

#include "../inc/preprocessor.h"
#include "../inc/compiler.h"

size_t  line = 1;
size_t  global_counter = 0;
size_t  start = 0;
size_t  end = 0;
t_macro *head = NULL;
bool    rewrite = false;

t_preproc *new_processor(char *define, char *value)
{
    t_preproc   *new;

    new = (t_preproc *)malloc(sizeof(t_preproc));
    new->define = strdup(define);
    new->value = strdup(value);
    new->next = NULL;
    return (new);
}

t_preproc   *add_processor(t_preproc *head, char *define, char *value)
{
    t_preproc   *trav;

    trav = head;
    while (trav->next)
        trav = trav->next;
    trav->next = new_processor(define, value);
    return (trav);
}

t_preproc   *push_preproc(t_preproc *head, char *define, char *value)
{
    t_preproc    *trav;

    trav = head;
    if (trav == NULL)
    {
        trav = new_processor(define, value);
    }
    else
    {
        trav = add_processor(head, define, value);
        trav = head;;
    }
    return (trav);
}

char    *skip_comments_m(char *buffer, size_t index)
{
    index++;
    if (buffer[index] == '/')
    {
        do
            index++;
        while (buffer[index] != '\n');
        line++;
    }
    else if (buffer[index] == '*')
    {
        do
        {
            index++;
            if (buffer[index] == '*')
            {
                index++;
                if (buffer[index] == '/')
                {
                    index++;
                    break ;
                }
            }
            else if (buffer[index] == '\n')
                line++;
        } while (42);
    }
    global_counter = index;
    return (NULL);
}

void    delete_preprocessor(t_preproc *head)
{
    t_preproc   *trav;

    while (head)
    {
        trav = head;
        head = head->next;
        free(trav->define);
        free(trav->value);
        free(trav);
    }
}

char        *skip_char(char *buffer, size_t start, size_t length)
{
    start++;
    do 
        start++;
    while (buffer[start] != '\'' && start < length);
    global_counter = start;
    return (NULL);
}

char        *skip_literal(char *buffer, size_t start, size_t length)
{
    start++;
    do
        start++;
    while (buffer[start] != '"' && start < length);
    global_counter = start;
    return (NULL);
}

size_t      skip_whitespace(char *buffer, size_t start, size_t length)
{
    for (;start < length; start++)
    {
        if (buffer[start] == '\t' || buffer[start] == ' ')
            continue ;
        else if (buffer[start] == '\n')
        { 
            line++;
            continue ;
        }
        else break ;
    }
    global_counter = start;
    return (start);
}

char         *get_macro_name(char *content, size_t index, size_t size)
{
    char    *name;

    name = NULL;
    while (content[index] != ' ' && content[index] != '\t' &&
        content[index] != '\n')
    {
        name = charpush(name, content[index]);
        index++;
    }
    global_counter = index;
    return (name);
}


char        *handle_macros(char *content, size_t size)
{
    size_t  i;
    char    *macro_name;
    
    size = strlen(content);
    i = global_counter;
    i = skip_whitespace(content, i, size);
    if (content[i] == '/' && (content[i + 1] == '/' || content[i + 1] == '>'))
        return (skip_comments_m(content, i));
    
    if (content[i] == '"') return (skip_literal(content, i, size));
    if (content[i] == '\'') return (skip_char(content, i, size));
    if (content[i] == '#')
    {
        start = i;
        i++;
        i = skip_whitespace(content, i, size);
        macro_name = get_macro_name(content, i, size);
        rewrite = true;
        return (macro_name);
    }
    global_counter =i;
    return (NULL);
}

// char  *handle_include(char *content, size_t sizei, char *filename)

char        *insertion(char *content, char *to_add)
{
    char    *new;

    new = (char *)malloc(sizeof(char) * (strlen(content) - (end - start) + strlen(to_add)));
    strncpy(new, content, start);
    strncpy(&new[start], to_add, strlen(to_add));
    strncpy(&new[start + strlen(to_add)], &content[end], strlen(content) - end + 1);
    printf("new is %s\n", new);
    return (new);
}

char        *scan_file(char *content, char *filename)
{
    size_t size;
    char *segment;
    char *string;
    char *newstring;
    global_counter = 0;
    t_macro *trav;

    size = strlen(content);
    while (global_counter < size)
    {
        string = handle_macros(content, size);
        if (string && strcmp(string, "include") == 0)
        {
            segment = handle_include(content, global_counter, filename); 
            if (segment)
            {
                newstring = insertion(content, segment);
                return (scan_file(newstring, filename));
            }
        }
       /* else if (string && (strcmp(string, "define") == 0)) 
        {
            trav = 
        }*/
        global_counter++; 
    }
}

t_preproc   *handle_preprocessor(int argc, char **argv)
{
    int     count;
    char    *content;
    size_t  file_size;

    count = 1;
    while (count < argc)
    {
        content = file_content(argv[count]);
        scan_file(content, argv[count]);
        //handle_macros(content, strlen(content));
        count++;
    }
  
}


int     main(int argc,char **argv)
{
    handle_preprocessor(argc, argv);
    return (0);
}











