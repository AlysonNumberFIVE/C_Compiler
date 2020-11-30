
#include <string.h>
#include <stdbool.h>

#define EQU_TOKEN_SIZE 10
#define SUM_TOKEN_SIZE 12

bool	equ_tokens(char *name)
{
	char tokens[10][4] = {
		"=\0",
		"!=\0",
		"+=\0",
		"-=\0",
		">>=\0",
		"<<=\0",
		"|=\0",
		"*=\0",
		"/=\0",
		"&=\0"
	};
	int 	count;

	count = 0;
	while (count < EQU_TOKEN_SIZE)
	{
		if (strcmp(tokens[count], name) == 0)
			return (true);
		count++;
	}
	return (false);
}


bool	sum_tokens(char *name)
{
	char tokens[12][4] = {
		"+\0",
		"-\0",
		"/\0",
		"*\0",
		"<<\0",
		">>\0",
		"||\0",
		"&&\0",
		"<\0",
		">\0",
		"==\0",
		"!=\0"
	};
	int count;
	
	count = 0;
	while (count < SUM_TOKEN_SIZE)
	{
		if (strcmp(tokens[count], name) == 0)
			return (true);
		count++;
	}
	return (false);
}




