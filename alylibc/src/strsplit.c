
#include "lib.h"


char **strsplit(char *str, char c)
{
	char **array;
	char *s;
	int i;

	s = NULL;
	array = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (s)
			{
				printf("ADDED : %s\n", s);
				array = arraypush(array, s);
				free(s);
				s = NULL;
			}
			else
				printf("NOT ADDED %s\n", s);
		}
		else
			s = charpush(s, str[i]);
		i++;
	}
	if (s)
	{
		array = arraypush(array, s);
		free(s);
	}
	return (array);
}
