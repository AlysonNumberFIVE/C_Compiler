
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
				array = arraypush(array, s);
				free(s);
				s = NULL;
			}
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
