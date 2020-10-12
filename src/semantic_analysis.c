

#include "../inc/token.h"
#include <ctype.h>
#include "../inc/database.h"
#include "../inc/semantic.h"
#include "../inc/compiler.h"
#define FUNCTION 1
#define WHILE 2
#define ARR 7
//#define IF 3
#define FOR 4
//#define DO 5 
t_struct *all_structs = NULL;
t_function *functions = NULL;
t_token	*to_evaluate = NULL;
char	**start = NULL;
t_stack *stack = NULL;

bool	value_found(char *value, char **to_scan)
{
	int		i;
	char		**double_words;

	i = 0;
	while (to_scan[i])
	{
		if (strcmp(value, to_scan[i]) == 0)
		{
			return (true);
		}
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

t_temp_var      *create_temp_var(t_token *token)
{
        int             depth;
        extern int      max_number;
        extern t_db     *list;
        t_hashtable     *variables;
        t_temp_var      *temp;
	t_token		*trav;
	char		*struct_manager;

        temp = (t_temp_var *)malloc(sizeof(t_temp_var));
        temp->depth = 0;
	temp->name = NULL;
	temp->type = NULL;
        trav = token;
	
	if (strcmp(trav->name, "struct") == 0)
	{
		struct_manager = join_with_space(trav->name, trav->next->name);
		if (value_found(struct_manager, start) == true)
		{
			temp->type = strdup(struct_manager);
			trav = trav->next->next;
		}
	}
        else if (value_found(trav->name, start) == true)
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

void	free_temp_var(t_temp_var *block)
{
	free(block->name);
	free(block->type);
	free(block);
}

bool	save_function(t_temp_var *temp_var, t_token *trav, char *function_name) 
{
                functions = push_function(functions, temp_var->name, temp_var->type, temp_var->depth);
                if (strcmp(trav->next->name, "void") == 0 && strcmp(trav->next->next->name, ")") == 0 &&
                        (strcmp(trav->next->next->next->name, ";") == 0 ||
                        strcmp(trav->next->next->next->name, "{") == 0))
                        return (true);

                trav = trav->next;
                t_fvars *variables;
                while (trav && strcmp(trav->name, ";") && strcmp(trav->name, "{"))
                {
                        if (strcmp(trav->name, ",") == 0 || strcmp(trav->name, ")") == 0)
                        {
                                if (!temp_var->name || !temp_var->type)
                                {
                                        printf("error : incorrect variable naming convention\n");
                                        return (false);
                                }
                                variables = create_new_parameter(temp_var->name, temp_var->type, temp_var->depth);
                                functions = new_parameter(functions, function_name, variables);
                                param_free(variables);
                                free_temp_var(temp_var);
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
                                trav = temp_var->curr;
                        }
                }
	return (true);
}


bool	validate_function(t_token *token)
{
	t_token 	*trav;
	char		*possible_function_name;
	extern t_db	*list;
	t_temp_var 	*temp_var;
	char		*value;

	temp_var = create_temp_var(token);
	if (temp_var == NULL)
		return (false);
	possible_function_name = strdup(temp_var->name);
	trav = temp_var->curr;	
	if (strcmp(trav->name, ";") == 0)
		insert_into_db(temp_var->type, temp_var->name, NULL, temp_var->depth);
	else if (strcmp(trav->name, "(") == 0)
		save_function(temp_var, trav, possible_function_name);
	else if (strcmp(trav->name, "=") == 0)
	{
		trav = trav->next;
		value = value_checker(trav);
		insert_into_db(temp_var->type, temp_var->name, value, temp_var->depth);
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
	bool		entering_command_block;
	bool		in_function;
	t_hashtable	*ff_list;
	t_token		*head;
	extern int	max_number;
	int		brackets;
	t_token		*error;	
	t_token		*back;
	bool		IS_ARR;

	IS_ARR = false;
	error = NULL;
	brackets = 0;
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
	entering_command_block = false;
	trav = tokens;
	head = trav;
	while (trav)
	{
		if (strcmp(trav->name, "{") == 0 )
		{
			if (prev && strcmp(prev, "=") == 0)
				IS_ARR = true;
			brackets++;
		}
		else if (strcmp(trav->name, "}") == 0)
		{
			IS_ARR = false;
			brackets--;
		}
		if (handle_native_csg(prev, trav->name) == 3)
		{
			drop_last_table();
			stack = pop_stack(stack);
		//	if (trav->next == NULL)
		//		break ;
		}
		else if (strcmp(trav->name, "struct") == 0)
		{
			trav = struct_loop(trav);
			if (strcmp(trav->name, ";") != 0)
				trav = error_recover(trav, "Missing semicolon", 
					push_token(error, ";", "SEMICOLON", trav->line, "NULL"));	
		}
		else if (entering_command_block == true)
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
		//	prev = trav->name;
			head = trav;
			entering_command_block = false;
		}
		else if (handle_native_csg(prev, trav->name) == SCOPE
			 || strcmp(trav->name, ";") == 0)
		{
			validate_function(head);
			head = trav;
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
		else if (trav->next && check_next_token(ff_list, trav->next->name, trav->name) == true)
		{
			if (strcmp(trav->name, ",") == 0 && IS_ARR == true && value_found(trav->next->name, start))
			{
				error = NULL;
				trav = forward_recovery(trav, "Error : can only have literals in arrays",
					push_token(error, "'CHAR'", "CHAR", trav->line, "NULL")); 
			//	back = trav;
			//	prev = trav->name;
			}
			if (scan_commands(commands, trav->name) && in_function == true)	
			{
				entering_command_block = true;
		//		continue ;
			}
			else if (scan_commands(commands, trav->name) && in_function == false)
				printf("error : can't have %s outside function scope\n",
					trav->name);
			prev = trav->name;
		}
		else
		{
			trav = panic_mode(trav, back, brackets);
		//	back = trav;
		//	prev = strdup(trav->name);
		}
		if (strcmp(trav->name, "}") && trav->next == NULL)
			break ;
		back = trav;
		prev = strdup(trav->name);
		trav = trav->next;
	}
	printf("SUMMARY =====\n");
	print_variables();
	print_structs(all_structs);
	print_functions(functions);
	return (true);
}

