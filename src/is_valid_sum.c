
#include "../inc/semantic.h"
#include "../inc/database.h"
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


bool is_valid_equation(t_token *tokens, char *end_token)
{
        extern int max_number;
        extern t_db **list;
    	char *db_value;
	t_token *equation;
        bool symbol;
        int brackets;

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
                        if (strcmp(equation->type, "ID") == 0)
                        {
                                db_value = get_from_db(equation->name);
                                if (db_value == NULL)
				{
                                        printf("Error found at this fucking pooint\n");
                                	return (false);
				}
                        } 
                        else if (strcmp(equation->type, "NUM") == 0 ||
				strcmp(equation->type, "CHAR") == 0 ||
				strcmp(equation->type, "LITERA") == 0)
			{
				symbol = true;
				if (strcmp(equation->type, "NUM") != 0)
					printf("Warning : mismatch in datatypes\n");
			}
			else
			{
				printf("equ : %s\n", equation->name);
				printf("error : A token or something is out of place\n");
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
                                printf("erron : invalid equation\n");\
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
        printf("symbol is %d\n", symbol);
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

