
#include <string.h>

int     endswith(char *string, char end)
{
    if (string[strlen(string) - 1] == end)
        return (1);
    return (-1);
}
