

#include "../inc/compiler.h"

bool is_valid_equation(char **equation)
{
        extern int max_number;
//      extern t_db **list;
        int counter;
        bool symbol;
//      char *db_value;
        int brackets;

	brackets = 0;
        symbol = false;
        counter = 0;
        while (equation[counter])
        {
                if (strcmp(equation[counter], "(") == 0)
                        brackets++;
                else if (strcmp(equation[counter], ")") == 0)
                        brackets--;
                else if (symbol == false)
                {
                        /*if (!atoi(equation[counter]))
                        {
                                db_value = get_from_db(equation[counter]);
                                if (db_value == NULL)
                                        printf("Error found at this fucking pooint\n");
                                else
                                {
                                        free(equation[counter]);
                                        equation[counter] = strdup(db_value);
                                        free(db_value);
                                }
                        }*/
                        symbol = true;
                }
                else if (symbol == true)
                {
                        if (strlen(equation[counter]) == 1 && strchr("+-/*^><|&", equation[counter][0]))
                                symbol = false;
                        else
                                printf("a new error is found\n");
		}
                counter++;
        }
	if (brackets != 0)
	{
		printf("error in brackets\n");
		return (false);
	}
        printf("symbol is %d\n", symbol);
        return (symbol);
}


int     main(void)
{
        char *sum = "1 + 2 * ( 42 / 2 ) * 11";
        sum = "1 + ( 162 + 1 * 2 * ( 11 * 2 ) + 4 + 5 ) / 2 + 3 < ( 42 )";

//      sum = "1 + 1";
        char **pieces = split(sum, ' ');
        is_valid_equation(pieces);
//      determine_sum(pieces);
        return (0);
}

