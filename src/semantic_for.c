

#include "../inc/token.h"
#include "../inc/semantic.h"
#include "../inc/compiler.h"




t_token	*semantic_for(char *prev, t_token *components, t_hashtable *ff_list)
{
	int commas;
	t_token	*sub_sequence;
	t_token *sub_prev;
	extern char **start;

	sub_sequence = NULL;
	commas = 0;
	components = components->next;
	if (strcmp(components->name, "(") == 0)
		components = components->next;

	while (components && handle_native_csg(prev, components->name) != SCOPE)
	{
		if (strcmp(components->name, ";") == 0)
		{			
			sub_sequence = push_token(sub_sequence,
				";", "SEMICOLON", components->line,
				components->filename);	
			validate_function(sub_sequence);
			t_token *h = sub_sequence;
			while (h)
			{
				printf("%s\n", h->name);
				h = h->next;
			}
			printf("==============\n");
			commas++;
			sub_sequence = NULL;
		} 
		else
		{
		/*	if (commas > 0 && value_found(components->name, start))
			{
				error_mode(components, "cannot declare datatype at this point");
			}*/
			if (components->next && check_next_token(ff_list, components->next->name, components->name) == false)
			{
				printf("here %s\n", components->name);
				printf("after here %s\n", components->next->name);
				error_mode(components, "lvalue must be a variable");	
			//	printf("Error detected with %s and %s\n", components->name,
			//		components->next->name);
			}
			//sub_sequence = arraypush(sub_sequence, components[counter]);
			sub_sequence = push_token(sub_sequence, 
				components->name, components->type, -1, 
				"thing");
		}
		sub_prev = components;
		prev = components->name;
		components = components->next;	
	}
	if (commas > 2)
		printf("too many commas\n");
	if (strcmp(components->name, "{") != 0)
		printf("incorrect way of formatting a for loop\n");
	return (components);
}
/*
int 	main(void)
{
	char *str = "( i = 0 ; 2141231241 ; 9109421 ; ; )";
	char **components = split(str, ' ');
	validate_for_loop(components);
	return (0);
} */



