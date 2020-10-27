


struct test {
	int i;
	struct test *next;
	int j;
};

int	main(void)
{
	struct test *pointer;

	pointer->next->next->next;
	return 0;
}
