
#include "../inc/token.h"
#include "../inc/symbol.h"
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

char		*this_var = NULL; // for printing out defective variable naming stuff.

t_function	*functions = NULL;
int		stack_height = 0;
t_pstack	*pstack = NULL;
t_hashtable	*ff_list = NULL;
bool		datatype_set = false;
char		*typing = NULL;
int		brackets = 0;
int		datatype_len = 0;
t_current_var	*current_variable = NULL;
int		asterisk_count = 0;
t_fcall		*current_call = NULL;


bool		false_error(t_token *token, int message);

t_current_var	*new_curr_var(char *name)
{
	t_current_var *new;

	new = (t_current_var *)malloc(sizeof(t_current_var));
	new->str = strdup(name);
	new->next = NULL;
	return (new);
}

t_current_var	*add_curr_var(t_current_var *head, char *name)
{
	t_current_var	*trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_curr_var(name);
	return (trav);
}

t_current_var	*push_curr_var(t_current_var *head, char *name)
{
	t_current_var	*trav;

	trav = head;
	if (trav == NULL)
	{
		trav = new_curr_var(name);
	}
	else
	{
		trav = add_curr_var(head, name);
		trav = head;
	}
	return (trav);
}

void		free_curr_var(t_current_var *head)
{
	t_current_var 	*trav;

	while (head)
	{
		trav = head;
		head = head->next;
		free(trav->str);
		free(trav);
	}
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
	bool flag;

	flag = false;
	if (datatype_len > 3)
		return (false_error(token, 3));
	if (legal_datatype(token->name) == false)
		return (false_error(token, 1));
	pstack = push_ptoken(pstack, token->name, token->type);
	datatype_len++;
	if (datatype_len > 0 && pstack)
	{
		if (token->next && strcmp(token->next->type, "DATATYPE") != 0)
		{
			if (is_datatype_correct(pstack, datatype_len) == false)
			{
				datatype_len = 0;
				return (false_error(token, 3));
			}
			datatype_len = 0;
			if (typing && strcmp(typing, "FUNCTION") == 0)
			{
				if (strcmp(token->next->type, "ID") == 0 || 
					strcmp(token->next->name, ",") == 0)
					return (true);
				else if (strcmp(token->next->type, "NUM") == 0 ||
					strcmp(token->next->type, "LITERAL") == 0)
					return (false_error(token, 16));
			}
		}	
	}
	return (true);	
}
bool	false_error(t_token *token, int message)
{
	printf("%s:%d: ", token->filename, token->line);
	if (message == 1) printf("error : expected ';', ',' or 'asm' before '%s' token\n\n", token->next->name);
	else if (message == 2) printf("error : unknown type name '%s'\n\n", token->next->name);
	else if (message == 3) printf("error : two or more data types in declaration specifiers\n\n");
	else if (message == 4) printf("error : expected declaration specifiers or '...' before '%s' token\n\n",
		token->next->name);
	else if (message == 5) printf("error : expected '}' at the end\n\n");
	else if (message == 6) printf("error : expected ',' or ';' before ')' token\n\n");
	else if (message == 7) printf("error : expected ';' before ')' token\n\n");
	else if (message == 8) printf("error : expected identifier or ')' before string or numeric constant\n\n");
	else if (message == 9) printf("error : expected identiifer or '(' before string or numeric constant\n\n");
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
	else if (message == 16) printf("error : expectin ';', ',' or ')' before numeric or string constant\n\n");
	else if (message == 17) printf("error : expected '}' at the end of input\n\n");
	else if (message == 18) printf("error : expected '{' at the end of input\n\n");
	else if (message == 19) printf("error : expected identifier or '(' before numeric or string constant\n\n");

	else if (message == 20) printf("error : suze of array has non-integer type\n\n");
	else if (message == 21) printf("error : expected expression before '%s' token\n\n",
		token->next->name);
	else if (message == 22) printf("error : conflicting type or redefiniton of variable '%s'\n\n", this_var); 
	else if (message == 23) printf("error : '%s' undeclared (first used in this function)\n\n",
		token->name); 
	else if (message == 24) printf("error : called object '%s' is not a function or function pointer\n\n",
		token->name);
	else if (message == 25) printf("error : lvalue required as left operand of assignment\n\n");
	else if (message == 26) printf("error : array '%s' assumed to have one element\n\n", 
		token->name); 
	clear_pstack();
	return (false);
}

bool	evaluate_id(t_token *token)
{
	char *pointer_number;
	int flag;
	pointer_number = NULL;

	printf("token is %s\n", token->name);
	if (!typing)
	{
		if (brackets < 0)
		{
			return (false_error(token, 15));
		}
	}
	else if (typing && strcmp(typing, "ASSIGN") == 0)
	{
		return (search_for_label(token->name, token->next->name));
	}
	else if (typing && strcmp(typing, "CALL") == 0)
	{
		current_call = add_call_params(current_call, token);
		if (token->next && strcmp(token->next->name, ",") == 0 ||
			strcmp(token->next->name, ")") == 0 ||
			strcmp(token->next->type, "NUM") == 0)
			return (true);
		else
		{
			return (false_error(token, 4));
		}
	}
	if (!pstack)
	{	
		if (token->next)
		{
			flag = search_for_label(token->name, token->next->name);
			if (flag == 1) return (false_error(token, 23));	
			else if (flag == 2) return (false_error(token, 24));
			if (strcmp(token->next->name, "(") == 0)
			{
				current_call = create_function_call(token->name);
				typing = strdup("CALL");
				return (true);
			}
		}
	}
	if (typing && strcmp(typing, "FUNCTION") == 0)
	{
		if (brackets < 0) return (false_error(token, 15));
	}
	if (token->next && strcmp(token->next->name, "(") == 0)
	{
		pstack = push_ptoken(pstack, token->name, token->type);
		pstack->construct = strdup("FUNCTION");	
		typing = strdup("FUNCTION");
	}
	else if (token->next && strcmp(token->next->name, ";") == 0)
	{
		pstack = push_ptoken(pstack, token->name, token->type);
		pstack->construct = strdup("VARIABLE");	
		typing = strdup("VARIABLE");
	}
	else if (token->next && strcmp(token->next->name, "[") == 0)
	{
		pstack = push_ptoken(pstack, token->name, token->type);
		pstack->construct = strdup("VARIABLE");
		typing = strdup("VARIABLE");
	}
	else if (token->next && strcmp(token->next->name, "=") == 0)
	{
		pstack = push_ptoken(pstack, token->name, token->type);
		pstack->construct = strdup("ASSIGN");
		typing = strdup("ASSIGN");	
	}
	else if (token->next && strcmp(token->next->name, "]") == 0)
	{
		pstack = push_ptoken(pstack, token->name, token->type);
		pstack->construct = strdup("ASSIGN");
		typing = strdup("ASSIGN");
	}
	else if (token->next && strcmp(token->next->name, ",") == 0 ||
			strcmp(token->next->name, ")") == 0 || 
			strcmp(token->next->name, "]") == 0) 
	{
		if (!typing || strcmp(typing, "FUNCTION") != 0)
			return (false);
	}
	else
	{
		if (!pstack) return (false_error(token, 2));
		else return (false_error(token, 12));
	}
	if (asterisk_count > 0)
		pointer_number = itoa(asterisk_count);
	else 
		pointer_number = strdup("0");	
	current_variable = push_curr_var(current_variable, pointer_number);
	current_variable = push_curr_var(current_variable, token->name);
	free(pointer_number);
	asterisk_count = 0;
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
	asterisk_count = 0;
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
	else if (typing && strcmp(typing, "CALL") == 0)
	{
	//	current_call = add_call_params(current_call, token);
		return (true);
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
	return (true);
}

bool	evaluate_bracket2(t_token *token)
{
	if (strcmp(typing, "FUNCTION") == 0) 
	{
		if (!token->next)
		{
			return (false_error(token, 17));
		}
		else if (token->next && strcmp(token->next->name, ";") == 0)
		{
			if (brackets > 0) return (false_error(token, 6));
			else if (brackets < 0) return (false_error(token, 7));
			// successful run : clean up and return true
			return (true);
		}
		else if (token->next && strcmp(token->next->name, ")") == 0 && brackets == 0)
		{
			printf("%s:%d: error : expected declaration specifier before ')' token\n\n"
				,token->filename, token->line);
		}
		else if (token->next && strcmp(token->next->name, "{") != 0 )
		{
			return (false_error(token, 18));
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
	}
	else if (typing && strcmp(typing, "CALL") == 0)
	{
		if (token->next && strcmp(token->next->type, "ID") == 0 ||
			strcmp(token->next->type, "NUM") == 0 || 
			strcmp(token->next->type, "LITERAL") == 0 ||
			strcmp(token->next->type, "CHAR") == 0)
			return (true);
		return (false_error(token, 4));
	}
}

bool	evaluate_number(t_token *token)
{
	extern t_token *left;
	extern t_token *right;
	
	if (typing && strcmp(typing, "FUNCTION") == 0) 
	{
		if (brackets > 0)
			return (false_error(token, 16));
		else
			return (false_error(token, 8));
	}
	else if (typing && strcmp(typing, "CALL") == 0)
	{
		current_call = add_call_params(current_call, token);
		if (token->next)
		{
			if (strcmp(token->next->name, ")") == 0 ||
				strcmp(token->next->name, ",") == 0)
				return (true);
			else
			{
				printf("CALL ERROR (498)\n");
				return (false_error(token, 4));
			}
		}
	}
	else if (typing && strcmp(typing, "ASSIGN") == 0)
	{
		if (!left) {
			left = push_token(left, token->name, 
			token->type, -1, token->filename);	
		}
		else if (!right) {
			right = push_token(right, token->name, 
			token->type, -1, token->filename);
		}
			
		evaluate_equation();
		if (token->next && equ_tokens(token->next->name) == true)
		{
			return (false_error(token, 25));
		}
		else if (token->next && sum_tokens(token->next->name) == true)
		{
			return (true);
		}
		else if (token->next && strcmp(token->next->name, ";") != 0)
		{
			return (false_error(token, 8));
		}
	}
	else if (!typing)
	{
		return (false_error(token, 19));
	}
	return (true);
}

bool	evaluate_asterisk(t_token *token)
{
	if (!pstack)
	{
		if (token->next && strcmp(token->next->name, "*") == 0 || 
			token->next && strcmp(token->next->name, "ID") == 0)
			return (true);
		else return (false_error(token, 21));	
	}
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
	else if (token->next && strcmp(token->next->type, "ID") != 0 &&
			strcmp(token->next->name, "*") != 0)
		return (false_error(token, 10));
	else if (!token->next)
		return (false_error(token, 13));
	asterisk_count++;
	return (true);
}

bool	evaluate_block1(t_token *token)
{
	if (typing && strcmp(typing, "ASSIGN") == 0)
	{
		if (token->next && strcmp(token->next->name, "NUM") != 0 ||
			strcmp(token->next->name, "ID") != 0)
			return (false_error(token, 26));
		else
			return (true);
	}
	else
	{
		if (token->next && strcmp(token->next->name, "]") == 0)
			return (true);
			
		else if (token->next && strcmp(token->next->type, "NUM") == 0)
			return (true);

		if (token->next && strcmp(token->next->type, "ID") == 0)
			return (true);
		if (token->next && strcmp(token->next->type, "NUM") != 0 ||
			strcmp(token->next->type, "ID") != 0 ||
			strcmp(token->next->name, "]") != 0)
			return (false_error(token, 20));
		else if (token->next && strcmp(token->next->type, "ID") == 0)
			printf("Check the type of this variable\n");
		else if (token->next && strcmp(token->next->name, "]") == 0)
			return (true);
		else 
			return (false_error(token, 21));
	}
	return (false_error(token, 10));
}

bool	evaluate_block2(t_token *token)
{
		
	if (typing && strcmp(typing, "VARIABLE") == 0 || strcmp(typing, "ASSIGN") == 0)
	{
		asterisk_count++;
		if (token->next && strcmp(token->next->name, "[") == 0 ||
			strcmp(token->next->name, "=") == 0 ||
			strcmp(token->next->name, ";") == 0)
				return (true);
		else if (token->next && strcmp(token->next->type, "NUM") == 0 ||
			strcmp(token->next->type, "LITERAL") == 0)
			return (false_error(token, 12));		
	}
	return (false_error(token, 1));
}

bool	evaluate_equ(t_token *token) 
{
	char *symbol_type;
	t_current_var *trav;
	int symtab_manager;
	extern t_token *left;

	if (asterisk_count > 0)
		current_variable = add_index_depth(current_variable, asterisk_count);
	trav = current_variable;
	while (trav)
	{
		printf(" %s | ", trav->str);
		trav = trav->next;
	}
	printf("%s\n\n\n", typing);
	left = push_token(left, current_variable->next->next->str, "ID", -1, token->filename);
	symtab_manager = symbol_table_manager(current_variable, typing);
	free_curr_var(current_variable);
	current_variable = NULL;
	asterisk_count = 0;	
	if (symtab_manager == 1) return (false_error(token, 22));
	if (typing && strcmp(typing, "VARIABLE") == 0)
	{
		if (token->next && strcmp(token->next->name, "{") == 0)
		{
			free(typing);
			typing = strdup("ARRAY");
			return (true);
		}
		else if (token->next && strcmp(token->next->type, "ID") == 0)
		{
			if (symbol_type && strcmp(symbol_type, "variable") == 0)
			{
				free(typing);
				typing = strdup("ASSIGN");
			}
			else if (symbol_type && strcmp(symbol_type, "function") == 0)
			{
				free(typing);
				typing = strdup("CALL");
			}
			else if (strcmp(token->next->type, "LITERAL") == 0 || 
				strcmp(token->next->type, "NUM") == 0)
			{
				free(typing);
				typing = strdup("ASSIGN");
			}
			return (true);		
		}	
	}
	else if (typing && strcmp(typing, "ASSIGN") == 0)
	{
		if (token->next && strcmp(token->next->type, "NUM") == 0 ||
			strcmp(token->next->type, "ID") == 0)
		{
			return (true);
		}
	}
}

bool	evaluate_semicolon(t_token *token)
{
	int symtab_manager;
	extern t_token *left;
	extern t_token *right;

	if (strcmp(token->name, ";") == 0)
	{
		// print current_var
		if (current_call)
		{
			verify_function_call(current_call);
			printf("current_call\n");
			printf("Function : %s\n", current_call->name);
			t_token *t = current_call->params;
			while (t)
			{
				printf("\t%s\n", t->name);
				t = t->next;
			}
			printf("\n\n");
		}
	//	verify_function_call(current_call);	
		if (asterisk_count > 0)
			current_variable = add_index_depth(current_variable, asterisk_count);
		t_current_var *trav = current_variable;
		while (trav)
		{
			printf(" %s | ", trav->str);
			trav = trav->next;
		} 
		printf(" %s\n\n\n", typing);
		symtab_manager = symbol_table_manager(current_variable, typing);	
		free_curr_var(current_variable);
		current_variable = NULL;
		free(typing);
		typing = NULL;
		asterisk_count = 0;
		if (left) 
		{
			free(left);
			left = NULL;
		}
		if (right)
		{
			free(right);
			right = NULL;
		}
		if (symtab_manager == 1) return (false_error(token, 22));
		clear_pstack();
		return (true);
	}
	return (false);
}

bool	evaluate_curly(t_token *token)
{
	extern int scope_depth;
	if (typing && strcmp(typing, "FUNCTION") == 0)
	{
		scope_depth++;
		free(typing);
		typing = NULL;
		free_curr_var(current_variable);
		current_variable = NULL;
		clear_pstack();
		if (token->next && strcmp(token->next->type, "ID") == 0 ||
			strcmp(token->next->type, "DATATYPE") == 0 ||
			strcmp(token->next->name, "*") == 0 ||
			strcmp(token->next->name, "}") == 0 ||
			strcmp(token->next->name, "NUM") == 0)
			return (true);
			
	}
	
	return (false);
}

bool	evaluate_curly2(t_token *token)
{
	extern int scope_depth;

	if (scope_depth == 0)	
		return (false_error(token, 10));
	drop_scope_block();
	if (typing)
	{
		free(typing);
		typing = NULL;
	}
	if (current_variable)
	{
		free_curr_var(current_variable);
		current_variable = NULL;
	}
	clear_pstack();
	return (true);
}

bool	evaluate_sum(t_token *token)
{

	if (token->next && strcmp(token->next->type, "ID") == 0 ||
		strcmp(token->next->type, "NUM") == 0)
	{
		return (true);
	}
	else
		return (false_error(token, 21));
}

void	error_cleanup(void)
{
	if (current_variable)
	{
		free_curr_var(current_variable);
		current_variable = NULL;
	}
	asterisk_count = 0;
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
		printf(" %s\n", trav->name);
		if (strcmp(trav->name, "(") == 0) brackets++;
		else if (strcmp(trav->name, ")") == 0) brackets--;

		// these tokens are allowed to start off a phrase
		if (strcmp(trav->type, "DATATYPE") == 0) guidance = evaluate_datatype(trav);
		else if (strcmp(trav->type, "ID") == 0) guidance = evaluate_id(trav);
		if (guidance == true)
		{
		//	if (strcmp(trav->type, "ID") == 0) guidance = evaluate_id(trav);
			if (strcmp(trav->name, "(") == 0) guidance = evaluate_bracket(trav);
			else if (strcmp(trav->name, "*") == 0) guidance = evaluate_asterisk(trav);
			else if (strcmp(trav->name, ")") == 0) guidance = evaluate_bracket2(trav);
			else if (strcmp(trav->name, ",") == 0) guidance = evaluate_comma(trav);
			else if (strcmp(trav->type, "NUM") == 0) guidance = evaluate_number(trav);
			else if (sum_tokens(trav->name) == true) guidance = evaluate_sum(trav);
			else if (equ_tokens(trav->name) == true) guidance = evaluate_equ(trav);
			else if (strcmp(trav->name, ";") == 0) guidance = evaluate_semicolon(trav);
			else if (strcmp(trav->name, "[") == 0) guidance = evaluate_block1(trav);
			else if (strcmp(trav->name, "]") == 0) guidance = evaluate_block2(trav);
			else if (strcmp(trav->name, "{") == 0) guidance = evaluate_curly(trav);
			else if (strcmp(trav->name, "}") == 0) guidance = evaluate_curly2(trav);
			
			if (guidance == false) 
			{
				error_cleanup();
			}
		}
		trav = trav->next;
	}
}
