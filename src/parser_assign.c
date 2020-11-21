

#include <ctype.h>
#include <limits.h>
#include "../inc/parser.h"
#include "../inc/symbol.h"

t_token	*left = NULL;
t_token	*right = NULL;

t_hashtable	*typesize_list = NULL;
t_hashtable	*type_and_their_sizes(void)
{
	t_hashtable	*typelist;
	int 		count;
	char 		*size;

	typelist = create_table(500);
	size = itoa(sizeof(char));
	ht_insert(typelist, "char", size); free(size);
	size = itoa(sizeof(signed char));
	ht_insert(typelist, "signed char", size); free(size);
	size = itoa(sizeof(unsigned char));
	ht_insert(typelist, "unsigned char", size); free(size);
	size = itoa(sizeof(short));
	ht_insert(typelist, "short", size); free(size);
	size = itoa(sizeof(short int));
	ht_insert(typelist, "short int", size); free(size);
	size = itoa(sizeof(signed short));
	ht_insert(typelist, "signed short", size); free(size);
	size = itoa(sizeof(signed short int)); 
	ht_insert(typelist, "signed short int", size); free(size);
	size = itoa(sizeof(unsigned short));
	ht_insert(typelist, "unsigned short", size); free(size);
	size = itoa(sizeof(unsigned short int));
	ht_insert(typelist, "unsigned short int", size); free(size);
	size = itoa(sizeof(int));
	ht_insert(typelist, "int", size); free(size);
	size = itoa(sizeof(signed));
	ht_insert(typelist, "signed", size); free(size);
	size = itoa(sizeof(signed int));
	ht_insert(typelist, "signed int", size); free(size);
	size = itoa(sizeof(unsigned));
	ht_insert(typelist, "unsigned", size); free(size);
	size = itoa(sizeof(unsigned int));
	ht_insert(typelist, "unsigned int", size); free(size);
	size = itoa(sizeof(long));
	ht_insert(typelist, "long", size); free(size);
	size = itoa(sizeof(long int));
	ht_insert(typelist, "long int", size); free(size);
	size = itoa(sizeof(signed long));
	ht_insert(typelist, "signed long", size); free(size);
	size = itoa(sizeof(signed long int));
	ht_insert(typelist, "signed long int", size); free(size);
	size = itoa(sizeof(unsigned long));
	ht_insert(typelist, "unsigned long", size); free(size);
	size = itoa(sizeof(unsigned long int));
	ht_insert(typelist, "unsigned long int", size); free(size);
	size = itoa(sizeof(long long));
	ht_insert(typelist, "long long", size); free(size);
	size = itoa(sizeof(long long int));
	ht_insert(typelist, "long logn int", size); free(size);
	size = itoa(sizeof(signed long long));
	ht_insert(typelist, "signed long long", size); free(size);
	size = itoa(sizeof(signed long long int));
	ht_insert(typelist, "signed long long int", size); free(size);
	size = itoa(sizeof(unsigned long long));
	ht_insert(typelist, "unsigned long long", size); free(size);
	size = itoa(sizeof(unsigned long long int));
	ht_insert(typelist, "unsigned long long int", size); free(size);
	/*
	size = itoa(sizeof(float));
	ht_insert(typelist, "float", size); free(size);
	size = itoa(sizeof(double));
	ht_insert(typelist, "double", size); free(size);
	size = itoa(sizeof(long double));
	ht_insert(typelist, "long double", size); free(size);
	*/
	return (typelist);
}

char		*it_is_always_stars(char *i)
{
	char *str;
	int count;
	char *tmp;
	int depth;

	depth = atoi(i);
	str = strdup(" ");
	count = 0;
	while (count < depth)
	{
		tmp = join(str, "*");
		free(str);
		str = strdup(tmp);
		free(tmp);
		count++;
	}
	return (str);
}

bool		typecheck_warning(t_variable *left, t_variable *right)
{
	char *ldepth;
	char *rdepth;
	char *left_token;
	char *right_token;
	char *star;

	ldepth = NULL;
	rdepth = NULL;
	if (left->depth > 0) ldepth = itoa(left->depth);
	if (right->depth > 0) rdepth = itoa(right->depth);
	if (ldepth)
	{
		star = it_is_always_stars(ldepth);
		left_token = join(left->type, star);
	}
	else 
		left_token = strdup(left->type);
	if (rdepth) 
	{
		star = it_is_always_stars(rdepth);
		right_token = join(right->type, star);
	}
	else 
		right_token = strdup(right->type);	
	printf("warning : initialization of '%s' from '%s' makes an integer from pointer type\n\n",
		left_token, right_token);
}

bool		datatype_comparison(t_variable *left, t_variable *right)
{
	if (left->depth != right->depth) 
	{
		typecheck_warning(left, right);
	}	
}

t_variable	*convert_literal_data(t_token *literal_data)
{
	char *type;
	char *name;
	int depth;
	t_variable *new;
	unsigned long long storage;

	new = NULL;
	if (typesize_list == NULL)
		typesize_list = type_and_their_sizes();
	if (strcmp(literal_data->type, "NUM") == 0)
	{
		depth = 0;
		if (isdigit(literal_data->name[0]))
		{
			storage = (unsigned long long)atoi(literal_data->name);
			if (storage < INT_MAX) type = strdup("int");
			else if (storage < UINT_MAX) type = strdup("unsigned int");
			else if (storage < LONG_MAX) type = strdup("long"); 
			else if (storage < ULONG_MAX) type = strdup("unsigned long int");
		}
		else if (literal_data->name[0] == '-')
		{
			storage = (signed long long )atoi(literal_data->name);
			if (storage > LONG_MIN) type = strdup("int");
			else if (storage > LONG_MIN) type = strdup("long int");
		}
	}
	else if (strcmp(literal_data->type, "LITERAL") == 0)
	{
		type = strdup("char");
		depth = 1;
	}
	new = push_variable(new, "TEMPORARY", type, depth);
	return (new);
}

bool	evaluate_equation(void)
{
	t_variable	*left_side;
	t_variable	*right_side;
	extern t_typecast *typecasting;
	
	if (typecasting) 
	{
		printf("typecast type  : %s\n", typecasting->type);
		printf("typecast depth : %d\n", typecasting->depth);
	}
	if (left && right)
	{
		if (left && strcmp(left->type, "ID") == 0) 
			left_side = search_variable(left->name);
		else if (left && strcmp(left->type, "NUM") == 0 || 
			strcmp(left->type, "LITERAL") == 0)
			left_side = convert_literal_data(left);
		if (strcmp(right->type, "ID") == 0)
			right_side = search_variable(right->name);
		else if (strcmp(right->type, "NUM") == 0 ||
			strcmp(right->type, "LITERAL") == 0)
			right_side = convert_literal_data(right);
		datatype_comparison(left_side, right_side);
		printf("left datatype  : %s\n", left_side->type);
		printf("right datatype : %s\n", right_side->type);
		left->type = strdup(right->type);
		left->name = strdup(right->name);
		free(right->name);
		free(right->type);
		free(right);
		right = NULL;	
	}
}

bool	evaluate_literal(t_token *token)
{
	extern char *typing;

	if (typing && strcmp(typing, "ASSIGN") == 0)
	{
		if (token->next && equ_tokens(token->next->name) == true)
			return (false_error(token, 25));
		else if (token->next && sum_tokens(token->next->name) == true ||
			strcmp(token->next->name, ";") == true) 
			return (true);
	}
	return (false_error(token, 9));
}


