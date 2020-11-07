

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../inc/parser.h"
#include <stdbool.h>
#include "../inc/compiler.h"

char datatypes[13][10] = {
	"unsigned\0",
        "short\0",
        "long\0",
        "int\0",
        "char\0",
        "void\0",
        "float\0",
        "double\0",
        "signed\0",
        "struct\0",
        "union\0"
};
/*
typedef struct s_parse_stack
{
	char *token;
	char *type;
	char *construct;
	struct s_parse_stack *next;
	struct s_parse_stack *prev;
}	t_pstack;
*/
int		stack_height = 0;
t_pstack	*pstack = NULL;
t_hashtable	*symbol_table = NULL;
t_hashtable	*ff_list = NULL;
bool		datatype_set = false;
char		*typing = NULL;
int		brackets = 0;


bool		false_error(t_token *token, int message);
void		init_symbol_table(void)
{
	symbol_table = create_table(600);
}

t_pstack	*new_ptoken(char *token, char *type)
{
	t_pstack *new;

	new = (t_pstack *)malloc(sizeof(t_pstack));
	new->token = strdup(token);
	new->type = strdup(type);
	new->construct = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}


t_pstack	*add_ptoken(t_pstack *head, char *token, char *type)
{
	t_pstack	*trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_ptoken(token, type);
	trav->next->prev = trav;
	trav = trav->next;
	return (trav);
}

t_pstack	*push_ptoken(t_pstack *head, char *token, char *type)
{
	t_pstack 	*trav;

	trav = head;
	if (trav == NULL)
	{
		trav = new_ptoken(token, type);
	}
	else
	{
		trav = add_ptoken(head, token, type);
	}
	if (typing)
		trav->construct = strdup(typing);
	stack_height++;
	return (trav);
}

void	clear_pstack(void)
{
	t_pstack *trav;
	if (typing)
	{
		free(typing);
		typing = NULL;
	}
	if (!pstack)
		return ;
	while (pstack)
	{
		trav = pstack;
		pstack = pstack->prev;
		free(trav->token);
		free(trav->type);
		free(trav);
	}
	pstack = NULL;
	stack_height = 0;
}

bool	legal_datatype(char *to_find)
{
	int i;

	i = 0;
	while (i < 13)
	{
		if (strcmp(datatypes[i], to_find) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	evaluate_datatype(t_token *token)
{
	if (stack_height > 3)
		return (false_error(token, 3));
	if (legal_datatype(token->name) == false)
		return (false_error(token, 1));
	pstack = push_ptoken(pstack, token->name, token->type);
	if (stack_height > 1)
	{
		if (token->next && strcmp(token->next->type, "DATATYPE") != 0)
			is_datatype_correct(pstack);
	
	}
	return (true);	
}
bool	false_error(t_token *token, int message)
{
	if (message == 1) printf("error : expected ';', ',' or 'asm' before '%s' token\n\n", token->next->name);
	else if (message == 2) printf("error : unknown type name '%s'\n\n", token->next->name);
	else if (message == 3) printf("error : two or more data types in declaration specifiers\n\n");
	else if (message == 4) printf("error : expected declaration specifiers or '...' before '%s' token\n\n",
		token->next->name);
	else if (message == 5) printf("error : expected '}' at the end\n\n");
	else if (message == 6) printf("error : expected ',' or ';' before ')' token\n\n");
	else if (message == 7) printf("error : expected ';' before ')' token\n\n");
	else if (message == 8) printf("error : expected identifier or ')' before numeric constant\n\n");
	else if (message == 9) printf("error : expected identiifer or '(' before numeric constant\n\n");
	else if (message == 10) printf("error : expected identifier or '(' before '%s' token\n\n",
		token->next->name);
	else if (message == 11) printf("error : expected identifier or ')' at end of input\n\n");
	else if (message == 12) printf("error : expected ';', ',', '=' or 'asm' before '%s'\n\n",
		token->next->name);
	else if (message == 13) printf("error : expected identifier or '(' at the end of input\n\n");
	else if (message == 14) printf("error : expected declaration specifiers before '%s' token\n\n",
		token->next->name);
	else if (message == 15) printf("error : declaration for parameter '%s' but no such poarameter\n\n",
		token->name);
	clear_pstack();
	return (false);
}

bool	evaluate_id(t_token *token)
{
	
	if (!typing)
	{
		if (brackets < 0)
		{
			return (false_error(token, 15));
		}
	}
	if (typing && strcmp(typing, "FUNCTION") == 0)
	{
		if (brackets < 0)
			return (false_error(token, 15));
	}
	if (token->next && strcmp(token->next->name, "(") == 0)
	{
		pstack = push_ptoken(pstack, token->name, token->type);
		pstack->construct = strdup("FUNCTION");	
		typing = strdup("FUNCTION");
	}
	else if (token->next && strcmp(token->next->name, ";") == 0 ||
			strcmp(token->next->name, "=") == 0)
	{
		pstack = push_ptoken(pstack, token->name, token->type);
		pstack->construct = strdup("VARIABLE");	
		typing = strdup("VARIABLE");
	}
	else if (token->next && strcmp(token->next->name, ",") == 0 ||
			strcmp(token->next->name, ")") == 0)
	{
		if (!typing || strcmp(typing, "FUNCTION") != 0)
			return (false);
	}
	else
	{
		if (!pstack) return (false_error(token, 2));
	//	if (!pstack) printf("error : unknown datatype '%s'\n\n", token->name);
		else return (false_error(token, 12));
	/*	printf("error : expected ';', ',', '=' or 'asm' before %s\n\n", token->next->name);	
		clear_pstack();
		return (false);*/
	}
	return (true);
}

bool	peek(t_token *token)
{
	char *value;
	char **segments;
	int i;

	value = ht_search(ff_list, token->name);
	if (!value)
		value = ht_search(ff_list, token->type);
	if (!value)
		return (false);
	segments = split(value, ' ');
	i = 0;
	while (segments[i])
	{
		if (strcmp(token->next->name, segments[i]) == 0 ||
			strcmp(token->next->type, segments[i]) == 0)
			return (true);
		i++;
	}
	free2d(segments);
	return (false);
}

bool	evaluate_bracket(t_token *token)
{
//	brackets++;
	if (typing && strcmp(typing, "FUNCTION") == 0)
	{
		if (token->next && strcmp(token->next->type, "DATATYPE") == 0 ||
			strcmp(token->next->name, ")") == 0)
		{
			return (true);
		}
		else if (token->next && strcmp(token->next->type, "NUM") == 0)
		{
			return (false_error(token, 4));
		}
		else if (token->next && strcmp(token->next->type, "ID") == 0)
		{
			return (false_error(token, 2));
		}
		else 
			return (false_error(token, 4));
	}
	if (token->next && (strcmp(token->next->type, "DATATYPE") == 0 ||
		strcmp(token->next->name, ")") == 0))
	{
		return (true);
	}
	else if (token->next && strcmp(token->next->type, "NUM") == 0)
	{
		return (false_error(token, 4));
	}
	
	else if (token->next && legal_datatype(token->next->name) == false)
	{
		if (strcmp(token->name, "ID") != 0)
			return (false_error(token, 4));
		else return (false_error(token, 2));
	}
	/*
	else if (token->next)
	{
		return (false_error(token, 4));
		
		printf("error : expected declaration specifiers or '...' before '%s' token\n\n",
			token->next->name);
		clear_pstack();
		return (false);
	} */
	return (true);
}

bool	evaluate_bracket2(t_token *token)
{
//	brackets--;
	if (strcmp(typing, "FUNCTION") == 0) 
	{
		if (!token->next)
		{
			printf("error : expected '}' at the end\n\n");
			clear_pstack();
			return (false);
		}
		else if (token->next && strcmp(token->next->name, ";") == 0)
		{
			if (brackets > 0) return (false_error(token, 6));
			else if (brackets < 0) return (false_error(token, 7));
			// successful run : clean up and return true
			clear_pstack();
			return (true);
		}
		else if (token->next && strcmp(token->next->name, ")") == 0 && brackets == 0)
		{
			printf("error : expected declaration specifier before ')' token\n\n");
		}
		else if (token->next && strcmp(token->next->name, "{") != 0 )
		{
			printf("error : expected '{' at the end\n\n");
			clear_pstack();
			return (false);	
		}
	}
	return (true);
}

bool	evaluate_comma(t_token *token)
{
	if (typing && strcmp(typing, "FUNCTION") == 0)
	{
		if (token->next && legal_datatype(token->next->name) == true)
			return (true);
		return (false_error(token, 4));
	/*	printf("error : expected declaration specifiers or '...' before '%s' token\n\n",
			token->next->name);
		clear_pstack();
		return (false);  */
	}
	printf("scope not set\n");
}

bool	evaluate_number(t_token *token)
{
	if (typing && strcmp(typing, "FUNCTION") == 0) 
	{
		if (brackets > 0)
		{
			printf("error : expected ';', ',' or ')' before numeric constant\n\n");
			clear_pstack();
			return (false);
		}
		else
			return (false_error(token, 8));
	}
	else if (typing && strcmp(typing, "VARIABLE") == 0)
	{
		if (token->next && strcmp(token->next->name, ";") != 0)
			return (false_error(token, 8));
	}
	return (true);
}

bool	evaluate_asterisk(t_token *token)
{
	if (typing && strcmp(typing, "FUNCTION") == 0)
	{
		if (token->next && strcmp(token->next->type, "NUM") == 0)
			return (false_error(token, 9));
	}
	else if (typing && strcmp(typing, "VARIABLE") == 0)
	{
		if (token->next && strcmp(token->next->type, "NUM") == 0)
			return (false_error(token, 9));
	}
	else if (token->next && strcmp(token->next->type, "ID") != 0)
		return (false_error(token, 10));
	else if (!token->next)
		return (false_error(token, 13));
}

void	print_error_line(t_token *token)
{
	extern t_file *files;
	t_file	*file;
	char **lines;

	file = files;
	while (file)
	{
		if (strcmp(file->filename, token->filename) == 0)
		{
			lines = split(file->solidcontent, '\n');
			printf("%s\n\n", lines[0]);
			free2d(lines);
			break;
		}	
		file = file->next;
	}	
}

bool	parser(t_token *token)
{
	t_token *trav;
	bool guidance;

	guidance = true;
	ff_list = first_and_follow();
	trav = token;
	while (trav)
	{
		if (strcmp(trav->name, "(") == 0) brackets++;
		else if (strcmp(trav->name, ")") == 0) brackets--;
		if (strcmp(trav->type, "DATATYPE") == 0)
		{
			guidance = evaluate_datatype(trav);
		}
		if (guidance)
		{
			if (strcmp(trav->type, "ID") == 0) guidance = evaluate_id(trav);
			else if (strcmp(trav->name, "(") == 0) guidance = evaluate_bracket(trav);
			else if (strcmp(trav->name, "*") == 0) guidance = evaluate_asterisk(trav);
			else if (strcmp(trav->name, ")") == 0) guidance = evaluate_bracket2(trav);
			else if (strcmp(trav->name, ",") == 0) guidance = evaluate_comma(trav);
			else if (strcmp(trav->type, "NUM") == 0) guidance = evaluate_number(trav);		
		//	if (guidance == false) print_error_line(trav);	
		}
		trav = trav->next;
	}
}
/*
int	main(void)
{
	return (0);
} */
