

#include <stdlib.h>

int     startswith(char *string, char start)
{
    if (string[0] == start)
        return (1);
    return (-1);
}
