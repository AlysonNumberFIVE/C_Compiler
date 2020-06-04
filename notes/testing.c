
#include <stdlib.h>

char    *string(void)
{
    printf("INSIDE\n");
    return (strdup("hello"));
}

int main(void)
{
    int value = 1 + 2 + 3 + string();
    return (0);
}
