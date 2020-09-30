

#include "lib.h"
#include <stdlib.h>

char **arraydup(char **array)
{
	char **new;
	int i;

	new = (char **)malloc(sizeof(char*) * (arraylen(array) + 1));
	i = 0;
	while (new[i])
	{
		new[i] = strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
