



#include "../inc/compiler.h"

#define ARRAY 1
#define SCOPE 2

int	handle_native_csg(char *prev, char *current)
{
	if (strcmp(current, "{") == 0)
	{
		if (strcmp(prev, "=") == 0)
			return (ARRAY);
		if (strcmp(prev, ")") == 0 || strcmp(prev, "do") == 0)
			return (SCOPE);
	}
	return (-1);
}
