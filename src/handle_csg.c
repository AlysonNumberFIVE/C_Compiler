



#include "../inc/compiler.h"

#define ARRAY 1
#define ENDSCOPE 3
#define SCOPE 2
#define ENDARRAY 4

int	handle_native_csg(char *prev, char *current)
{
	if (strcmp(current, "{") == 0)
	{
		if (strcmp(prev, "=") == 0)
			return (ARRAY);
		if (strcmp(prev, ")") == 0 || strcmp(prev, "do") == 0)
			return (SCOPE);
	}
	if (strcmp(current, "}") == 0)
	{
		if (strcmp(prev, ";") == 0 || strcmp(prev, "}") == 0)
			return (ENDSCOPE);
		else
			return (ENDARRAY); 
	}
	return (-1);
}
