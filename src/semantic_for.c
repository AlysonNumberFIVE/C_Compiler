



#include "../inc/compiler.h"

bool	validate_for_loop(char **components)
{
	int commas;
	int counter;
	char **sub_sequence;

	sub_sequence = NULL;
	counter = 0;
	commas = 0;
	while (components[counter] && strcmp(components[counter], ")") != 0)
	{
		if (strcmp(components[counter], ";") == 0)
		{
			printf("process sub_squence\n");
			commas++;
			free2d(sub_sequence);
			sub_sequence = NULL;
		} 
		else
			sub_sequence = arraypush(sub_sequence, components[counter]);
		counter++;
	}
	if (commas > 2)
		printf("too many commas\n");
}

int 	main(void)
{
	char *str = "( i = 0 ; 2141231241 ; 9109421 ; ; )";
	char **components = split(str, ' ');
	validate_for_loop(components);
	return (0);
}



