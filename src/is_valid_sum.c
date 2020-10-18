
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
	while (trav)
	{
		printf(" %s ", trav->name);
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
	printf("function name : %s\n", funct->function_name);
	printf("function type : %s\n", funct->type);
	printf("function depth : %d\n", funct->depth);
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
	printf("EXTRACTION  := ");
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
	printf("end extractin\n");
	new = push_token(new, ";", "SEMICOLON", trav->line, trav->filename);
	return (new);		
}

bool test_function_evaluation(t_token *function)
{
	t_token	*carry;
	t_token	*halt;
	t_token	*temp;
	t_function *to_eval;
	t_token	*function_test;
	t_token *new;
	

	to_eval = get_function(function->name);
	carry = function->next->next;
	while (carry)
	{
		printf("carry is %s\n", carry->name);
	
		if (strcmp(carry->type, "ID") == 0 && strcmp(carry->next->name, "(") == 0)
		{
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
	return (true);
}

bool	eval_function_type(char *function_name)
{
	t_functino *the_function;
 
	the_function = get_function(function_name);
		
}

bool is_valid_equation(t_token *tokens, char *end_token)
{
        extern int max_number;
        extern t_db **list;
    	char *db_value;
	t_token *equation;
        bool symbol;
        int brackets;
	t_token	*halt;
	t_token	*temp;
	t_token *function_test;

	function_test = NULL;
	brackets = 0;
        symbol = false;
	equation = tokens;
	printf("ENTERING IS_VALID_SUM\n");
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
                        if (strcmp(equation->type, "ID") == 0 && strcmp(equation->next->name, "(") != 0)
                        {
                                db_value = get_from_db(equation->name);
                                if (db_value == NULL)
				{
                                        printf("Error found at this fucking pooint\n");
                                	return (false);
				}
                        } 
			else if (strcmp(equation->type, "ID") == 0 && strcmp(equation->next->name, "(") == 0)
			{
				function_test = extract_function(equation);
				halt = equation;
				temp = extract_function_type(halt->name, halt);
				print_segment(function_test);
				
				test_function_evaluation(function_test);
	
				halt->next = temp;
				equation = skip_function(equation);
				temp->next = equation;
				if (!equation)
					return (true);	
			}
                        else if (strcmp(equation->type, "NUM") == 0 ||
				strcmp(equation->type, "CHAR") == 0 ||
				strcmp(equation->type, "LITERAL") == 0)	
			{
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

