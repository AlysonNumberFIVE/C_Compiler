

#include <ctype.h>
#include "../inc/database.h"
#include "../inc/semantic.h"
#include "../inc/compiler.h"
#define FUNCTION 1
#define WHILE 2
#define IF 3
#define FOR 4
#define DO 5
t_function *functions = NULL;
t_token	*to_evaluate = NULL;
char	**start = NULL;
t_stack *stack = NULL;

bool	value_found(char *value, char **to_scan)
{
	int		i;

	i = 0;
	while (to_scan[i])
	{
		if (strcmp(value, to_scan[i]) == 0)
			return (true);
		i++;
	}
	return (false);
} 



bool	validate_literal(char *str)
{
	if (str[0] == '\"' && str[strlen(str) - 1] == '\"')
		return (true);
	return (false);
}

bool	validate_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}




typedef struct s_variable_block
{
        char *name;
        char *type;
        t_token *curr;
        int depth;
}       t_temp_var;

t_temp_var      *create_temp_var(t_token *token)
{
        int             depth;
        extern int      max_number;
        extern t_db     *list;
        t_hashtable     *variables;
        t_temp_var      *temp;
	t_token		*trav;

        temp = (t_temp_var *)malloc(sizeof(t_temp_var));
        temp->depth = 0;
        trav = token;
        if (value_found(trav->name, start) == true)
        {
                temp->type = strdup(trav->name);
                trav = trav->next;
        }
        else
                return (NULL);

        while (strcmp(trav->name, "*") == 0)
        {
                temp->depth++;
                trav = trav->next;
        }
        if (strcmp(trav->type, "ID") == 0)
        {
                temp->name = strdup(trav->name);
                trav = trav->next;
        }
        else
                return (NULL);
        temp->curr = trav;
        return (temp);
}



bool	validate_function(t_token *token)
{
	t_token 	*trav;
	char		*name;
	char		*type;
	char		*value;
	int		depth;
	extern int	max_number;
	extern t_db	*list;
	t_hashtable	*variables;
	t_temp_var 	*temp_var;

	temp_var = create_temp_var(token);
	if (temp_var == NULL)
		return (false);
	name = temp_var->name;
	type = temp_var->type;
	depth = temp_var->depth;
	trav = temp_var->curr; 
/*	depth = 0;
	value = NULL;
	type = NULL;
	name = NULL;
	trav = token;
	if (value_found(trav->name, start) == true)
	{
		type = strdup(trav->name);
		trav = trav->next;
	}
	else
	{
		printf("curr %s\n", trav->name);
		printf("stdup %s\n", trav->next->name);
		printf("Datatype error\n");
		return (false);
	}
	
	while (strcmp(trav->name, "*") == 0)
	{
		depth++;
		trav = trav->next;
	}
	if (strcmp(trav->type, "ID") == 0)
	{
		name = strdup(trav->name);
		trav = trav->next;
	}
	else
	{
		printf("Incorrect variable naming\n");
		return (false);
	} */
	if (strcmp(trav->name, ";") == 0)
	{
		printf("DONE\n");
		insert_into_db(type, name, NULL, depth);
	}
	else if (strcmp(trav->name, "(") == 0)
	{
		functions = push_function(functions, name, type, depth);
		if (strcmp(trav->next->name, "void") == 0 && strcmp(trav->next->next->name, ")") == 0 &&
			(strcmp(trav->next->next->next->name, ";") == 0 ||
			strcmp(trav->next->next->next->name, "{") == 0))
			return (true);
				
		trav = trav->next;
		char *pname;
		char *ptype;
		int pdepth;
		pname = NULL;
		ptype = NULL;
		pdepth = 0;
		t_fvars *variables;
		while (trav && strcmp(trav->name, ";") && strcmp(trav->name, "{"))
		{
			if (strcmp(trav->name, ",") == 0 || strcmp(trav->name, ")") == 0)
			{
				if (!pname || !ptype)
				{
					printf("error : incorrect variable naming convention\n");
					return (false);
				}
				variables = create_new_parameter(pname, ptype, depth);
				functions = new_parameter(functions, name, variables);
				param_free(variables);
				free_and_null(&pname);
				free_and_null(&ptype);
				pdepth = 0;
				if (strcmp(trav->name, ")") == 0)
				{
					trav = trav->next;
					break;
				}
				trav = trav->next;
			}
			else
			{
			
				temp_var = create_temp_var(trav);
				pname = temp_var->name;
				ptype = temp_var->type;
				pdepth = temp_var->depth;
				trav = temp_var->curr;
				/*if (value_found(trav->name, start) == true)
				{
					ptype = strdup(trav->name);
					trav = trav->next;
				}	
				else
				{
					printf("Incorrect way to create parameter vars\n");
					return (false);
				}
				while (trav && strcmp(trav->name, "*") == 0)
				{
					depth++;
					trav = trav->next;
				}
				if (strcmp(trav->type, "ID") == 0)
				{
					pname = strdup(trav->name);
					trav = trav->next;
				}
				else
				{
					printf("Incorrect variable naming\n");	
					return (false);
				}*/
			}
		}	
	}
	else if (strcmp(trav->name, "=") == 0)
	{
		trav = trav->next;
		value = value_checker(trav);
//		update_variable_value(name, value);
		insert_into_db(type, name, value, depth);
		//return (is_valid_equation(trav, ";"));
	}
	return (true);
}


char	*determine_token_type(char *token)
{
	if (validate_id(token) == true)
		return (strdup("ID"));
	else if (validate_literal(token) == true)
		return (strdup("LITERAL"));
	else if (validate_num(token) == true)
		return (strdup("NUM"));
	else if (token[0] == '\'' && token[strlen(token) - 1] == '\'')
		return (strdup("CHAR"));
	return (strdup(token));
}


bool	check_next_token(t_hashtable *ff_list, char *next_token, char *current_token)
{
	char	*name;	
	char 	*value;	
	char 	*second;
	char 	**pieces;	
	
	name = determine_token_type(current_token);
	value = ht_search(ff_list, name);
	if (value)
	{
		if (strcmp(value, "DONE") == 0)
			return (true);
		pieces = split(value, ' ');
		second = determine_token_type(next_token);
		if (value_found(second, pieces) == true)
			return (true);
	}
	return (false);
}

bool	scan_commands(char **commands, char *to_find)
{
	int i;

	i = 0;
	while (commands[i])
	{
		if (strcmp(commands[i], to_find) == 0)
			return (true);
		i++;
	}
	return (false);
}

char	**command_blocks(void)
{
	char **blocks;
	char *list = "for while if";
	blocks = split(list, ' ');
	return (blocks);
}

bool	semantic_analysis(t_token *tokens)
{
	t_token		*trav;
	char		**next;
	char		**commands;
	char		*prev;
	bool		flag_token;
	bool		in_function;
	t_hashtable	*ff_list;
	t_token		*head;
	extern int	max_number;
	
	max_number= 0;
	in_function = false;
	start = split("char const void struct int short double float size_t long longlong signed void", ' ');
        ff_list = first_and_follow();
	commands = command_blocks();
	if (value_found(tokens->name, start) == false)
	{
		printf("Your code is shit and you deserve to die\n");
		return (false);
	}
	flag_token = false;
	trav = tokens;
	head = trav;
	while (trav)
	{
		if (handle_native_csg(prev, trav->name) == 3)
		{
			drop_last_table();
			stack = pop_stack(stack);
			if (trav->next == NULL)
				break ;
		//	 trav = trav->next;
		}
		else if (flag_token == true)
		{
			if (strcmp(trav->name, "for") == 0)
				trav = semantic_for(prev, trav);
			/*
			else if (strcmp(trav->name, "while") == 0)
				trav = semantic_while(prev, trav);
			else if (strcmp(trav->name, "if") == 0) printf("handle if statement\n");
			*/
			stack = push_stack(stack, FOR);
			add_new_table();
			prev = trav->name;
		//	trav = trav->next;
			head = trav;
			flag_token = false;
		}
		else if (handle_native_csg(prev, trav->name) == SCOPE
			 || strcmp(trav->name, ";") == 0)
		{
			validate_function(head);
			head = trav;
		//	trav = trav->next;
			if (strcmp(trav->name, "{") == 0)
				add_new_table();
			if (head && strcmp(head->name, ";") == 0)
				head = head->next;
			else if (head && strcmp(head->name, "{") == 0 && in_function == false)
			{
				stack = push_stack(stack, FUNCTION);
				in_function = true;
			}
		}
		else if (check_next_token(ff_list, trav->next->name, trav->name) == true)
		{
			if (scan_commands(commands, trav->name) && in_function == true)
			{
				flag_token = true;
				continue ;
			}
			else if (scan_commands(commands, trav->name) && in_function == false)
				printf("error : can't have %s outside function scope\n",
					trav->name);
			prev = trav->name;
		//	trav = trav->next;
		}
		else
		{
			printf("This was a failed expedition : %s\n", trav->name);
			// skipping entire line.
			return (false);
		}
		if (strcmp(trav->name, "}") && trav->next == NULL)
			break ;
		trav = trav->next;
	}
	printf("SUMMARY =====\n");
	print_variables();
	print_functions(functions);
	return (true);
}

