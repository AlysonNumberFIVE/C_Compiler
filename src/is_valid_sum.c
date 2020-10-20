
#include "../inc/typing.h"
#include "../inc/semantic.h"
#include "../inc/database.h"
#include "../inc/token.h"
#include "../inc/compiler.h"

bool valid_operator(char *token)
{
	char operators[20][10] = {
		"+\0",
		"-\0",
		"<<\0",
		">>\0",
		"&&\0",
		"||\0",
		"/\0",
		"*\0"
	};
	int operator_array_len = 8;
	int counter;

	counter = 0;
	while (counter < operator_array_len)
	{
		if (strcmp(token, operators[counter]) == 0)
			return (true);
		counter++;
	}
	return (true);
}

t_token *extract_function(t_token *token)
{
	t_token *trav;
	t_token	*function;
	int	brackets;

	function = NULL;
	function = push_token(function, token->name, token->type, token->line, token->filename);
	trav = token;
	trav = trav->next;
	brackets = 0;
	while (trav)
	{
		if (strcmp(trav->name, "(") == 0)
			brackets++;
		else if (strcmp(trav->name, ")") == 0)
			brackets--;
		function = push_token(function, trav->name, trav->type, trav->line, trav->filename);
		if (brackets == 0)
			break ;
		trav = trav->next;
	}
	function = push_token(function, ";", "SEMICOLON", trav->line, trav->filename);
	return (function);	
}

t_token *convert_function_to_token(char *function_name)
{
	t_function	*target;
	extern t_function	*functions;

	target = get_function(function_name);
	// experimenta.
	t_token	*test = NULL;
	test = push_token(test, "test", "NUM", 42, "apache.php.c");
	return (test);
}

t_token *skip_function(t_token *token)
{
	t_token *trav;
	int brackets;

	trav = token;
	trav = trav->next;
	brackets = 0;
	printf("SKIPPING FUNCTION ===========\n");
	while (trav)
	{
		printf(" -------> %s ", trav->name);
		if (strcmp(trav->name, "(") == 0)
			brackets++;
		else if (strcmp(trav->name, ")") == 0)
			brackets--;
		trav = trav->next;
		if (brackets == 0)
			break;
	}
	return (trav);
}

t_token	*extract_function_type(char *function_name, t_token *token)
{
	t_function 	*funct;
	t_token		*custom_block;
	char		*custom_datatype;

	custom_block = NULL;
	funct = get_function(function_name);
	custom_datatype = join(itoa(funct->depth), funct->type);
	custom_block = push_token(custom_block, "function_name", custom_datatype, 
		token->line, token->filename);
	return (custom_block);
}

void	print_segment(t_token *function)
{
	t_token	*trav;

	trav = function;
	while (trav)
	{
		printf("%s ", trav->name);
		trav = trav->next;
	}
	printf("\n");
}


t_token *skip_section(t_token *token)
{
	t_token *trav;
	int brackets;
	bool bracket_flag;
	
	bracket_flag = false;
	brackets = 0;
	trav = token;
	while (trav && strcmp(trav->name, ",") != 0)
	{
		if (strcmp(trav->name, "(") == 0)
		{
			bracket_flag = true;
			brackets++;
		}
		else if (strcmp(trav->name, ")") == 0)
			brackets--;
		if (brackets <= 0 && bracket_flag == true)
			break;
		trav = trav->next;
	}
	return (trav);
}
t_token	*extract_section(t_token *token)
{
	t_token	*trav;
	t_token	*new;
	int	brackets;
	bool	bracket_flag;
		
	bracket_flag = false;
	trav = token;
	new = NULL;
	brackets = 0;
	while (trav && strcmp(trav->name, ",") != 0)
	{
		printf(" %s ", trav->name);
		if (strcmp(trav->name, "(") == 0)
		{
			bracket_flag = true;
			brackets++;
		}
		else if (strcmp(trav->name, ")") == 0)
			brackets--;
		if (brackets == 0 && bracket_flag == true)
			break ;	
		if (brackets < 0)
			break ;
		new = push_token(new, trav->name, trav->type, trav->line, trav->filename);
		trav = trav->next;
	}
	new = push_token(new, ";", "SEMICOLON", trav->line, trav->filename);
	return (new);		
}

int	type_len(t_token *list)
{
	int count;
	t_token *trav;	

	trav = list;
	count = 0;
	while (trav)
	{
		trav = trav->next;
		count++;
	}
	return (count);
}

bool	evaluate_function_parameters(char *function_name, t_token *type_list)
{
	t_token	*trav;
	t_fvars **parameters;
	t_function *to_get;
	int counter;	
	t_function *test_function;
	t_db	*object;

	counter = 0;
	to_get = get_function(function_name);
	if (type_len(type_list) != to_get->param_number)
	{
		printf("Error : Incorrect parameters for function \"%s\"\n", to_get->function_name);
		return (false);
	}
	parameters = to_get->parameters;
	trav = type_list;
	while (trav)
	{
		if (strcmp(trav->type, "LITERAL") == 0)
		{
			printf("LITERAL check\n");
			if (strcmp(parameters[counter]->type, "char") == 0 &&
				parameters[counter]->depth == 1)
				printf("pass\n");
			else
			{
				printf("incorrect parameter type value : %s\n", trav->name);
				break;
			}
		}
		else if (strcmp(trav->type, "ID") == 0)
		{
			printf("ID Check\n");
			object = get_object_from_db(trav->name);
			if (object)
			{
				if (object->depth == parameters[counter]->depth &&
					strcmp(object->type, parameters[counter]->type) == 0)
					printf("pass\n");
				else
				{
					printf("Incorrect parameter value : %s\n", trav->name);
					break;
				}
			}
			if (!object)
			{
				test_function = get_function(trav->name);
				if (test_function)
				{
					if (test_function->depth == parameters[counter]->depth &&
						strcmp(test_function->type, parameters[counter]->type) == 0)
						printf("pass\n");
					else
					{
						printf("Incorrect parameter value : %s\n", trav->name);
						break ;
					}
				}
			}
		}
		else if (strcmp(trav->type, "NUM") == 0)
		{
			printf("NUM check\n");
			if (!strcmp(parameters[counter]->type, "int") == 0)
			{
				printf("Incorrect parameter value : number expected\n");
				break ;
			}
		}
		counter++;	
		trav = trav->next;
	}
}

void DELETE(t_token *assert)
{
	t_token *trav;

	trav = assert;
	while (trav)
	{
		printf(" %s ", trav->type);
		trav = trav->next;
	}
	printf("\n\n\n");
}

bool test_function_evaluation(t_token *function)
{
	t_token	*carry;
	t_token	*halt;
	t_token	*temp;
	t_function *to_eval;
	t_token	*function_test;
	t_token *new;
	t_token *param_assert;
	char *param_name;	

	param_name = strdup(function->name);
	param_assert = NULL;
	to_eval = get_function(function->name);
	carry = function->next->next;
	while (carry && strcmp(carry->name, ";") != 0)
	{
		if (strcmp(carry->type, "ID") == 0 && strcmp(carry->next->name, "(") == 0)
		{
		
			param_assert = push_token(param_assert, carry->name,
				carry->type,  carry->line, carry->filename);
			function_test = extract_function(carry);
			halt = carry;	
			temp = extract_function_type(halt->name, halt);
		
			print_segment(function_test);
	
			test_function_evaluation(function_test);
			
			carry = skip_function(carry);
						
			halt->next = temp;
			temp->next = carry;	
		}
		else 
		{
			param_assert = push_token(param_assert, carry->name,
				carry->type, carry->line, carry->filename);
			new = extract_section(carry);
			print_segment(new);
			carry = skip_section(carry);
			if (!carry)
				break;
		//	carry = carry->next;
			is_valid_equation(new, ",");
		}
		carry = carry->next;
	}
	DELETE(param_assert);
	evaluate_function_parameters(param_name, param_assert);
	return (true);
}

t_this_type	*get_current_function_type(t_token *token)
{
	t_function	*function;
	t_this_type	*current_type;
	function = get_function(token->name);
	if (!function)
	{
		printf("Error : function not found\n");
		return (NULL);
	}
	current_type->datatype = function->type;
	current_type->depth = function->depth;
	return (current_type);
}

t_this_type	*get_current_variable_type(t_token *token)
{
	t_db	*object;
	t_this_type *current_type;

	current_type = (t_this_type *)malloc(sizeof(t_this_type));
	if (strcmp(token->type, "ID") == 0)
	{
		object = get_object_from_db(token->name);
		current_type->datatype = strdup(object->name);
		current_type->depth = object->depth;
	}
	else if (strcmp(token->type, "LITERAL") == 0)
	{
		current_type->datatype = strdup("char");
		current_type->depth = 1;
	}
	else if (strcmp(token->type, "NUM") == 0 || strcmp(token->type, "CHAR") == 0)
	{
		current_type->datatype = strdup("int");
		current_type->depth = 0;
	}
	else
	{
		free(current_type);
		current_type = NULL;
	}
	return (current_type);
}

bool	eval_function_type(char *function_name, t_token *token)
{
	t_function *this_function;
	extern t_this_type *current_type; 

	this_function = get_function(function_name);
	if (this_function->depth != current_type->depth)
	{
		error_mode(token, "Incompatible datatypes without casting");
		return (false);
	}
	return (true);
}

bool	eval_variable_type_match(char *variable, t_token *token)
{
	t_db *object;
	extern t_this_type *current_type;	

	object = get_object_from_db(variable);
	if (object->depth != current_type->depth)
	{
		error_mode(token ,"incompatible datatypes without casting");
		return (false);
	}
	return (true);
	/*if (
	if (object->depth != current->depth)
	*/	
}


bool	type_comparison(t_token *prev, t_token *current)
{
	t_this_type	*tprev;
	t_this_type	*tcurrent;

	t_function	*function_prev;
	t_db		*object_prev;
	t_function	*function_current;
	t_db		*object_current;

	tprev = (t_this_type *)malloc(sizeof(t_this_type));
	tcurrent = (t_this_type *)malloc(sizeof(t_this_type));
	if (strcmp(prev->type, "ID") == 0)
	{
		object_prev = get_object_from_db(prev->name);
		if (!object_prev)
		{
			function_prev = get_function(prev->name);
			tprev->datatype = strdup(function_prev->type);
			tprev->depth = function_prev->depth;
		}
		else
		{
			tprev->datatype = strdup(object_prev->type);
			tprev->depth = object_prev->depth;
		}
	}
	else if (strcmp(prev->type, "LITERAL") == 0)
	{
		tprev->datatype = strdup("char");
		tprev->depth = 1;
	}
	else if (strcmp(prev->type, "NUM") == 0 || strcmp(prev->type, "CHAR") == 0)
	{
		tprev->datatype = strdup("int");
		tprev->depth = 0;
	}
	

	if (strcmp(current->type, "ID") == 0)
	{
		object_current = get_object_from_db(current->name);
		if (!object_current)
		{
			function_current = get_function(current->name);
			tcurrent->datatype = strdup(function_current->type);
			tcurrent->depth = function_current->depth;
		}
		else
		{
			tcurrent->datatype = strdup(object_current->type);
			tcurrent->depth = object_current->depth;
		}
	}
	else if (strcmp(current->type, "LITERAL") == 0)
	{
		tcurrent->datatype = strdup("char");
		tcurrent->depth = 1;
	}
	else if (strcmp(current->type, "NUM") == 0 || strcmp(current->type, "CHAR") == 0)
	{
		tcurrent->datatype = strdup("int");
		tcurrent->depth = 0;
	}

	if (strcmp(tcurrent->datatype, tprev->datatype) == 0 &&
		tcurrent->depth == tprev->depth)
		return (true);
	printf("Error : variable datatype size mismatch\n");
	return (false);
}



t_token	*skip_struct_info(t_token *token)
{
	while (token && strcmp(token->next->name, "->") == 0)
	{
		token = token->next->next;
	}
	return (token);
}

bool handle_pointer_dereferencing(t_token *pointer)
{
	int depth_to_minus;
	t_function *this_function;
	t_db *object;
	t_this_type *deref;

	depth_to_minus = 0;
	deref = (t_this_type *)malloc(sizeof(t_this_type));
	while (pointer && strcmp(pointer->name, "*") == 0)
	{
		depth_to_minus++;
		pointer = pointer->next;
	}
	if (strcmp(pointer->type, "ID") != 0)
	{
		printf("Error : Incorrect use of pointer dereferncing\n");
	}
	if (strcmp(pointer->next->name, "(") == 0)
	{
		this_function = get_function(pointer->name);
		deref->depth = this_function->depth - depth_to_minus;
		deref->datatype = this_function->type;
		printf("run function check\n");
	}
	else if (strcmp(pointer->next->name, "->") == 0 || 
		strcmp(pointer->next->name, ".") == 0)
	{
		printf("Fail the shit\n");	
		return (false);
	}
	else
	{
		object = get_object_from_db(pointer->name);
		if (!object)
		{
			printf("Error : variable \"%s\" doesn't exist\n", pointer->name);
			return (false);
		}
		deref->depth = object->depth - depth_to_minus;
		deref->datatype = strdup(object->type);
	}
	
}

bool is_valid_equation(t_token *tokens, char *end_token)
{
	extern t_this_type *current_type;
        extern int max_number;
        extern t_db **list;
    	t_db *db_value;
	t_token *equation;
        bool symbol;
        int brackets;
	t_token	*halt;
	t_token	*temp;
	t_token *function_test;


	// handling type comparisontra
	t_token *prev;
	prev = NULL;

	function_test = NULL;
	brackets = 0;
        symbol = false;
	equation = tokens;
        while (equation && (strcmp(equation->name, end_token)))
        {	
		if (strcmp(equation->name, ";") == 0)
			break ;
                if (strcmp(equation->name, "(") == 0)
                        brackets++;
                else if (strcmp(equation->name, ")") == 0)
                        brackets--;
                else if (symbol == false)
                {
			if (strcmp(equation->name, "*") == 0)
			{
				handle_pointer_dereferencing(equation);
				while (equation && strcmp(equation->name, "*") == 0)
					equation = equation->next;
				if (strcmp(equation->next->name, ";") == 0)
					break;
			}
			if (strcmp(equation->name, "@") == 0)
			{
				equation = equation->next;
				if (strcmp(equation->type, "ID") != 0)
				{
					printf("%s ", equation->name);
					printf("Error : incorrect use of memory referencing\n");
					return (false);
				}
				if (strcmp(equation->next->name, ";") == 0)
					break;	
				equation = equation->next;
			}
			else if (strcmp(equation->type, "ID") == 0 && strcmp(equation->next->name, "->") == 0)
			{
				handle_struct_dereferencing(equation);
				// skip struct stuff.
				equation = skip_struct_info(equation);
				equation = equation->next;
			}
                        else if (strcmp(equation->type, "ID") == 0 && strcmp(equation->next->name, "(") != 0)
                        {
				if (prev)
					type_comparison(prev, equation);
			        prev = equation;
				db_value = get_object_from_db(equation->name);
				
                                if (db_value == NULL)
				{
                                        printf("Error found at this fucking pooint\n");
                                	return (false);
				}
				symbol = true;				
			} 
			else if (strcmp(equation->type, "ID") == 0 && strcmp(equation->next->name, "(") == 0)
			{	
				if (prev)
					type_comparison(prev, equation);
				prev = equation;
				function_test = extract_function(equation);
				halt = equation;
				temp = extract_function_type(halt->name, halt);
	 				print_segment(function_test);
				
				test_function_evaluation(function_test);
	
				halt->next = temp;
				printf("BEFORE SKIPPING  %s\n", equation->name);
				equation = skip_function(equation);
				temp->next = equation;
				if (!equation)
					return (true);

			} 
                        else if (strcmp(equation->type, "NUM") == 0 ||
				strcmp(equation->type, "CHAR") == 0 ||
				strcmp(equation->type, "LITERAL") == 0)	
			{
				if (prev)
					type_comparison(prev, equation);
				prev = equation;
				symbol = true;
			}
			else
			{
				symbol = true;
				error_mode(equation, "Error : incompatible datatype"); 
				//printf("error : A token or something is out of place\n");
				return (false);
			}
                }
                else if (symbol == true)
                {
			if (strcmp(equation->name, "!") == 0)
				equation = equation->next;
			if (valid_operator(equation->name))
                                symbol = false;
                        else
			{
                                //printf("erron : invalid equation\n");
				return (false);
			}
		}
	
        	equation = equation->next;
	}
	if (brackets != 0)
	{
		printf("error in brackets\n");
		return (false);
	}
 //       printf("symbol is %d\n", symbol);
        return (true);
}

/*
int     main(void)
{
        char *sum = "1 + 2 * ( 42 / 2 ) * 11";
        sum = "1 + ( 162 + 1 * 2 * ( 11 * 2 ) + 4 + 5 ) / 2 + 3 < ( 42 )";

//      sum = "1 + 1";
        char **pieces = split(sum, ' ');
        is_valid_equation(pieces);
//      determine_sum(pieces);
        return (0);
}*/

