
#include "../inc/semantic.h"
#include "../inc/token.h"
#include "../inc/compiler.h"

t_token	*panic_mode(t_token *trav, t_token *back, int brackets)
{
	t_token	*error;
	extern t_stack *stack;
	extern char **start;

	if (strcmp(trav->type, "ID") == 0 || strcmp(trav->type, "NUM") == 0 || 
		strcmp(trav->type, "LITERAL") == 0 || strcmp(trav->type, "CHAR") == 0)
       	{
		if (stack && stack->scope_name == 4)
                {
               		error = NULL;
                       	trav = error_recover(trav, "Error: missing semilcolon",
                        	push_token(error, ";", "SEMICOLON", trav->line, "NULL"));
                }
                else if (brackets != 0)
                {
                       	error = NULL;
                        trav = forward_recovery(trav, "Error : missing a closing '}'",
                        	push_token(error, "}", "CLOSINGBRACKET", trav->line, "NULL"));
                 }
                 else
                 {
                 	error = NULL;
                        trav = forward_recovery(trav, "Error : missing semicolon",
                        	push_token(error, ";", "SEMICOLON", trav->line, "NULL"));
                }
         }
         else if (strcmp(trav->name, "}") == 0)
         {
          	error = NULL;
          	trav = forward_recovery(trav, "Error: missing semicolon",
                	push_token(error, ";", "SEMICOLON", trav->line, "NULL"));
         }
         else if (strcmp(trav->name, ",") == 0)
         {
          	if (strcmp(back->type, "CHAR") == 0)
                {
                	error = NULL;
                        trav = forward_recovery(trav, "Error: Incomplete list",
                                push_token(error, "'C'", back->type, trav->line, "NULL"));
                }
         }
         else if (value_found(trav->name, start) == true)
         {
          	error = NULL;
                trav = forward_recovery(trav, "Error: variable missing",
                        push_token(error, "X", "ID", trav->line, "NULL"));
         }
	 return	(trav);
}
