#include <ctype.h>
#include "../inc/token.h"
#include "../inc/compiler.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

size_t  read_count = 0;
size_t  line = 0;
t_hashtable *table = NULL;

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


t_token     *number_found(char *buffer, size_t index)
{
    char    *var_name;
    bool    is_float;

    is_float = false;
    var_name = NULL;
    do
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
        if (buffer[index] == '.')
        {
            is_float = true;
            index++;
        }
    }
    while (isdigit(buffer[index]));
    read_count = index;
    if (is_float == true)
        return new_token(var_name, "FLOAT");
    return new_token(var_name, "NUMBER");
}

t_token     *skip_comments(char *buffer, size_t index)
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
    read_count = index;
    return (NULL);
}

t_token     *literal_found(char *buffer, size_t index)
{
    char    *var_name;
    t_token *token;

    var_name = NULL;
    do 
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
    }
    while (buffer[index] != '\"');
    var_name = charpush(var_name, buffer[index]);
    index++;
    read_count = index;
    token =  new_token(var_name, "LITERAL");
    free(var_name);
    return (token);
}

t_token     *character_found(char *buffer, size_t index)
{
    char    *var_name;
    t_token *token;
    int counter;
    int max;

    max = 2;
    counter = 0;
    var_name = NULL;
    do
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
        if (buffer[index] == '\\' && buffer[index + 1] == '\'')
            max = 3;
        counter++;
    }
    while (counter < max);
    var_name = charpush(var_name, buffer[index]);
    index++;
    read_count = index;
    token = new_token(var_name, "CHAR");
    free(var_name);
    return token;
}

static bool macro_phrase(char *to_check)
{
    int counter;
    extern char hashes[5][10];

    counter = 0;
    while (counter < 5)
    {
        if (strcmp(to_check, hashes[counter]) == 0)
            return (true );
        counter++;
    }
    return (false);
}

static bool reserved_word(char *to_check)
{
    int counter;
    extern char reserved[33][9]; 
    
    counter = 0;
    while (counter < 32)
    {
        if (strcmp(to_check, reserved[counter]) == 0)
            return (true);
        counter++;
    }
    return (false);
}

t_token     *macro_found(char *buffer, size_t index)
{
    char    *var_name;
    t_token *token;

    var_name = NULL;
    do
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
    }
    while (isalnum(buffer[index]) || buffer[index] == '_');
    read_count = index;
    token = new_token(var_name, "MACRO");
    free(var_name);
    return token;
}

t_token     *header_found(char *buffer, size_t index)
{
    char    *var_name;
    t_token *token;

    var_name = NULL;
    do
    {
        var_name = charpush(var_name, buffer[index]);
        index++;
    }
    while (buffer[index] != '>');
    index++;
    read_count = index;

    token = new_token(var_name, "HEADER");
    free(var_name);
    return token;
}

t_token     *id_found(char *buffer, size_t index)
{
    char    *var_name;
    t_token *token;

    var_name = NULL;
    do 
    {    
        var_name = charpush(var_name, buffer[index]);
        index++;
    }
    while (isalnum(buffer[index]) || buffer[index] == '_'); // ||
      //     buffer[index] == '-' || buffer[index] == '>' || 
      //     buffer[index] == '.');
    //
    // Add a check for checking for reserved words.
    //
    
    read_count = index;
    if (reserved_word(var_name) == true)
        token = new_token(var_name, "KEYWORD");
    else
        token = new_token(var_name, "ID");
    //free(var_name);
    return (token);
}

t_token     *single_token(char *buffer, size_t index, char *tok_name)
{
    char    *var_name;
    t_token *tok;

    var_name = NULL;
    var_name = charpush(var_name, buffer[index]);
    index++;
    read_count = index;
    tok = new_token(var_name, tok_name);
    //free(var_name);
    return tok;
}
void        print_range(char *buffer, size_t start, size_t end)
{
    size_t i = start;

    while (i < end)
    {
        printf("%c", buffer[i]);
        i++;
    }
    printf("\n\n\n");
}

/*
t_token     *two_sym_token(char *buffer,size_t index, char first, char second, 
            char *first_name, char *second_name)
{
    char    *var_name;
    t_token *token;
    char    *which;

    var_name = NULL;
    var_name = charpush(var_name, first);
    which = first_name;
    if (buffer[index + 1] == second)
    {
        var_name = charpush(var_name, second);
        which = second_name;
    }
    token = new_token(var_name, which);
    read_count = index + 2;
    free(var_name);
    return token;
} */

t_hashtable *key_token(void);

t_token     *two_sym_token(char *buffer, size_t index, t_hashtable *table, char *first_name)
{
    char    *value;
    char    *var_name;
    char    *test;
    t_token *token;
   
    var_name = NULL;
    token = NULL;
    test = NULL;
    var_name = charpush(var_name, buffer[index]);
    test = charpush(test, buffer[index]);
    test = charpush(test, buffer[index + 1]);
    value = ht_search(table, test);
    if (value == NULL)
    {
        token = new_token(var_name, first_name);
        index++;
    }
    else
    {
        if ((strcmp(test, "<<") == 0 || strcmp(test, ">>") == 0) && 
            buffer[index + 2] == '=')
        {
            test = charpush(test, buffer[index + 2]);
            value = ht_search(table, test);
            index++;
        }
        token = new_token(test, value);
        index += 2;
    }
    read_count = index;
    free(test);
    free(var_name);
    return (token);
}

t_token     *scan(char *buffer, t_hashtable *table)
{
    size_t  i;
    size_t  buff_size;
    char    *temp;

    buff_size = strlen(buffer);
    for (i = read_count; i < buff_size; i++)
    {
        if (buffer[i] == ' ' || buffer[i] == '\t')
            continue;
        else if (buffer[i] == '\n')
            line++;
        else
            break;
    }
    read_count = i + 1;
    printf("LIne is %zu\n", line);
    switch (buffer[i])
    {
        /*
        case '&':
            if (buffer[i + 1] == '&') 
            {
                read_count = i + 2;
                return new_token("&&", "AND"); 
   L         }
            else return new_token("&", "BITAND");
        case '|':
            if (buffer[i + 1] == '|') 
            {
                read_count = i + 2;
                return new_token("||", "OR"); 
            }
            else return new_token("|", "BITOR");
        case '=':
            if (buffer[i + 1] == '=') 
            {
                read_count = i + 2;
                return new_token("==", "EQ"); 
            }
            else return new_token("=", "ASSIGN");
        case '!':
            if (buffer[i + 1] == '=') 
            {
                read_count = i + 2;
                return new_token("!=", "NE");
            }
            else return new_token("!", "NOT");  */
        case '<':
            if (buffer[i + 1] == '=') 
            {
                read_count = i + 2;
                return new_token("<=", "LE"); 
            }
            else if (isalpha(buffer[i + 1]))
                return header_found(buffer, read_count);
            else return new_token("<", "LESS");
       /*
        case '>':
            if (buffer[i + 1] == '=') 
            {
                read_count = i + 2;
                return new_token(">=", "GE"); 
            }
            else return new_token(">", "GREATER");
        */   
    }
    read_count = i; 
    if (buffer[read_count] == '/' && (buffer[read_count + 1] == '/' || buffer[read_count + 1] == '*'))
        return (skip_comments(buffer, read_count));

    if (buffer[read_count] == '&') return (two_sym_token(buffer, read_count, table, "BINTAND"));
    if (buffer[read_count] == '|') return (two_sym_token(buffer, read_count, table, "BITOR"));
    if (buffer[read_count] == '=') return (two_sym_token(buffer, read_count, table, "ASSIGN"));
    if (buffer[read_count] == '!') return (two_sym_token(buffer, read_count, table, "NOT"));
    if (buffer[read_count] == '>') return (two_sym_token(buffer, read_count, table, "GREATER"));
    if (buffer[read_count] == '%') return (two_sym_token(buffer, read_count, table, "MOD"));
    if (buffer[read_count] == '+') return (two_sym_token(buffer, read_count, table, "PLUS"));
    if (buffer[read_count] == '-') return (two_sym_token(buffer, read_count, table, "MINUS"));
    if (buffer[read_count] == '/') return (two_sym_token(buffer, read_count, table, "DIV"));
    if (buffer[read_count] == '*') return (two_sym_token(buffer, read_count, table, "MULTI"));
    if (buffer[read_count] == '^') return (two_sym_token(buffer, read_count, table, "XOR"));
    /*
    if (buffer[read_count] == '&') return (two_sym_token(buffer, read_count, '&', '&', "BITAND", "AND"));
    if (buffer[read_count] == '|') return (two_sym_token(buffer, read_count, '|', '|', "BITOR", "OR"));
    if (buffer[read_count] == '=') return (two_sym_token(buffer, read_count, '=', '=', "ASSIGN", "EQ"));
    if (buffer[read_count] == '!') return (two_sym_token(buffer, read_count, '!', '=', "NOT", "NE"));;
    if (buffer[read_count] == '>') return (two_sym_token(buffer, read_count, '>', '=', "GREATER", "GE"));
    */
    read_count = i;
    if (isalpha(buffer[read_count]) || buffer[read_count] == '_') 
        return (id_found(buffer, read_count));
    if (isdigit(buffer[read_count])) return (number_found(buffer, read_count));
    if (buffer[read_count] == '#') return (macro_found(buffer, read_count));
    if (buffer[read_count] == '\"') return (literal_found(buffer, read_count));
    if (buffer[read_count] == '\'') return (character_found(buffer, read_count));
    if (buffer[read_count] == ';') return (single_token(buffer, read_count, "SEMICOLON"));
    if (buffer[read_count] == '(') return (single_token(buffer, read_count, "OPENBRACKET"));
    if (buffer[read_count] == ')') return (single_token(buffer, read_count, "CLOSEBRACKET")); 
    if (buffer[read_count] == '{') return (single_token(buffer, read_count, "OPENBRACE"));
    if (buffer[read_count] == '}') return (single_token(buffer, read_count, "CLOSEBRACE"));
    if (buffer[read_count] == '+') return (single_token(buffer, read_count, "PLUS"));
    if (buffer[read_count] == '-') return (single_token(buffer, read_count, "MINUS"));
    if (buffer[read_count] == '%') return (single_token(buffer, read_count, "MODULO"));
    if (buffer[read_count] == ',') return (single_token(buffer, read_count, "COMMA"));
    if (buffer[read_count] == '/') return (single_token(buffer, read_count, "DIVIDE"));
    if (buffer[read_count] == '*') return (single_token(buffer, read_count, "MULTI"));
    if (buffer[read_count] == '?') return (single_token(buffer, read_count, "QMARK"));
    if (buffer[read_count] == ':') return (single_token(buffer, read_count, "COLON"));
    if (buffer[read_count] == '[') return (single_token(buffer, read_count, "OPENSQUARE"));
    if (buffer[read_count] == ']') return (single_token(buffer, read_count, "CLOSESQUARE"));
    if (buffer[read_count] == '.') return (single_token(buffer, read_count, "DOT"));
    if (buffer[read_count] == '\\') return (single_token(buffer, read_count, "LINECONT"));
    if (buffer[read_count] == '~') return (single_token(buffer, read_count, "TILDE"));
    if (buffer[read_count] == '^') return (single_token(buffer, read_count, "^"));

    return (NULL);
}



void    print_token(t_token *token)
{
    t_token *trav;

    trav = token;
    while (trav)
    {
        printf("%s : %s\n", trav->name, trav->type);
        trav = trav->next;
    }
}


// testing 
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

t_hashtable     *key_token(void)
{
    t_hashtable *table;

    table = create_table(1000);
    ht_insert(table, "+=", "ADD_ASSIGN");
    ht_insert(table, "-=", "SUB_ASSIGN");
    ht_insert(table, "*=", "MUL_ASSIGN");
    ht_insert(table, "/=", "DIV_ASSIGN");
    ht_insert(table, "%=", "MOD_ASSIGN");
    ht_insert(table, "^=", "XOR_ASSIGN");
    ht_insert(table, "|=", "OR_ASSIGN");
    ht_insert(table, ">>", "RIGHT_OP");
    ht_insert(table, "<<", "LEFT_OP");
    ht_insert(table, "<<=", "LEFT_OP_ASSIGN");
    ht_insert(table, ">>=", "RIGHT_OP_ASSIGN");
    ht_insert(table, "&&", "AND");
    ht_insert(table, "||", "OR");
    ht_insert(table, "&=", "AND_ASSIGN");
    ht_insert(table, "<=", "LE_OP");
    ht_insert(table, ">=", "GE_OP");
    ht_insert(table, "==", "EQ_OP");
    ht_insert(table, "++", "INC_OP");
    ht_insert(table, "--", "DEC_OP");
    ht_insert(table, "!=", "NE_OP");;
    ht_insert(table, "->", "PTR_OP");
    return (table);
}

int main(int argc, char **argv)
{
    char *buffer = test_file(argv[1]);
    //printf("%s\n", buffer);
    t_hashtable *table;
    
    table = key_token(); 
    t_token *list = NULL;
    size_t size = strlen(buffer);
    while (read_count < size)
    {
        t_token *temp = scan(buffer, table);
        if (temp)
            list = push_token(list, temp->name, temp->type);
    }
    print_token(list);

    return (0);
}



