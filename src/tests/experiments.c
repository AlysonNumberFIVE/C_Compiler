

#include <stdio.h>

//string str = NULL;
char *null;
int x = 42;
typedef struct test {
	struct test *next;
	struct x{
		int a;
	}*b;
};

struct a {
	int i;
	int j;
	int k;
};

struct b {
	int a;
	int b;
	int c;
};
int main(void)
{
	int x = 1;

	if (42) {
		extern int x;
		printf("x is %d\n", x);
	}
	return (0);
}
