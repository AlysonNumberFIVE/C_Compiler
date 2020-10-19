


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

void	v(char *str);


int main(void)
{
	char *str = "hello";	
	int x;
	x = 4 && (&str);

	return (0);
}
