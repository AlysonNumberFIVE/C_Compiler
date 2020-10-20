


//string str = NULL;

struct test {
	struct test *next;
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

char	*v(char *str);


int main(void)
{
	char *str = "hello";	
	struct b testing;

	*str = 42;	
	return (0);
}
