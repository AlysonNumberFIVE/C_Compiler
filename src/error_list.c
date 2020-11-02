
#include "../inc/semantic.h"
#include "../inc/token.h"
#include "../inc/compiler.h"
#include "../inc/database.h"

void	error_type_checker(t_token *first, t_token *second)
{
	extern t_file *files;
	t_token	*nfirst;
	t_function *function;
	t_db *object;
	t_token *nsecond;

	if (strcmp(first->type, "LITERAL") == 0 || strcmp(second->type, "LITERAL") == 0)
	{
		printf("%s %d Warning : adding literal can cause undefined behaviour\n",
			first->filename, first->line);
		if (strcmp(first->name, "LITERAL") == 0)
			print_error_message(first);
		else
			print_error_message(second);
	}
	else
	{
		if (strcmp(first->type, "ID") == 0) 
		{
			object = get_object_from_db(first->name);
			if (!object)
			{
				function = get_function(first->name);
			}
		}
	}
}

void	print_error_message(t_token *position)
{
	t_file	*trav;
	extern t_file *files;

	trav = files;

	while (trav)
	{
		if (strcmp(position->filename, files->filename) == 0)
		{
			if (arraylen(trav->content) < position->line)
				exit(1);
			printf(": %s\n\n", trav->content[position->line]);
			break;
		}
		trav = trav->next;
	}
}

t_token	*error_mode(t_token *token, char *message)
{
	t_token *trav;
	extern char **start;
	if (!token)
		return (trav);
	trav = token;
	printf("%s : %d ", token->filename, token->line);
	printf("Error : %s : '%s'\n", message, token->name);
	print_error_message(token);
	while (trav)
	{
		if (value_found(trav->name, start) || strcmp(trav->name, ";") == 0)
			break;
		trav = trav->next;
	}
	return (trav);
}

t_token	*panic_mode(t_token *trav, t_token *back, int brackets)
{
	t_token	*error;
	extern t_stack *stack;
	extern char **start;

	if (strcmp(back->type, "PTR_OP") == 0)
	{
		error = NULL; printf("%s %d ", trav->filename, trav->line);
		trav = error_recover(trav, "incorrect pointer dereferencing",
			push_token(error, "ERROR", "ID", trav->line, trav->filename));
		print_error_message(back);
		trav = trav->next;
	}	
	else if (strcmp(trav->type, "ID") == 0 || strcmp(trav->type, "NUM") == 0 || 
		strcmp(trav->type, "LITERAL") == 0 || strcmp(trav->type, "CHAR") == 0)
       	{
		if (stack && stack->scope_name == 4)
                {
               		error = NULL; printf("%s %d ", trav->filename, trav->line);
                       	trav = error_recover(trav, "missing semilcolon",
                        	push_token(error, ";", "SEMICOLON", trav->line, trav->filename)); 
			print_error_message(trav);	
			trav = trav->next;
                }
                else if (brackets != 0)
                {
                       	error = NULL; printf("%s %d ", trav->filename, trav->line);
                        trav = forward_recovery(trav, "missing a closing '}'",
                        	push_token(error, "}", "CLOSINGBRACKET", trav->line, trav->filename));
                	print_error_message(trav);
		}
                 else
                 {
                 	error = NULL; printf("%s %d ", trav->filename, trav->line - 1);
                        trav = forward_recovery(trav, "missing semicolon",
                        	push_token(error, ";", "SEMICOLON", trav->line, trav->filename));
                	print_error_message(trav);
			trav = trav->next;
		}
         }
         else if (strcmp(trav->name, "}") == 0)
         {
          	error = NULL; printf("%s %d ", trav->filename, trav->line);
          	trav = forward_recovery(trav, "missing semicolon",
                	push_token(error, ";", "SEMICOLON", trav->line, trav->filename));
        	print_error_message(trav); 
	}
         else if (strcmp(trav->name, ",") == 0)
         {
          	if (strcmp(back->type, "CHAR") == 0)
                {
                	error = NULL; printf("%s %d ", trav->filename, trav->line);
                        trav = forward_recovery(trav, "incomplete list",
                                push_token(error, "'C'", back->type, trav->line, trav->filename));
                	print_error_message(trav);
		}
         }
         else if (value_found(trav->name, start) == true)
         {
          	error = NULL; printf("%s %d ", trav->filename, trav->line);
                trav = forward_recovery(trav, "variable missing",
                        push_token(error, "X", "ID", trav->line, trav->filename));
        	print_error_message(trav); 
	}
	 return	(trav);
}
