



#include "../inc/compiler.h"
#include "../inc/semantic.h"
#include "../inc/token.h"


t_token *semantic_if(char *prev_name, t_token *token, t_hashtable *ff_list)
{
        t_token *trav;
        t_token *sub_sequence;
        t_token *assignent;
        t_token *prev;
        int counter;
        extern char **start;
        char *prev_type;
        bool found;
        char *test;

        test = NULL;
        found = false;
        counter = 0;
        sub_sequence = NULL;
        trav = token;
        trav = trav->next;
        if (strcmp(trav->name, "(") == 0)
                trav = trav->next;

        while (trav && handle_native_csg(trav->name, trav->next->name) != SCOPE)
        {
                if (value_found(trav->name, start))
                        error_mode(trav, "Error : variable declaration forbidden in while loops\n");
                if (trav->next && check_next_token(ff_list, trav->next->name, trav->name) == false)
                        printf("unspecified error %s and %s\n", trav->name, trav->next->name);
                sub_sequence = push_token(sub_sequence, trav->name, trav->type,
                        trav->line, trav->filename);
                prev = trav;
                trav = trav->next;
                counter++;
        }
        sub_sequence = push_token(sub_sequence, ";", "SEMICOLON", trav->line, trav->filename);
        if (is_valid_equation(sub_sequence, ";"))
        {
                return (trav);
        }
	error_mode(trav, "syntax error in if statement");
        return (trav);
}

