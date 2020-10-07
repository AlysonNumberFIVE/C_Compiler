

#include "../inc/token.h"
#include "../inc/semantic.h"
#include "../inc/compiler.h"

t_token	*semantic_for(char *prev, t_token *components)
{
	int commas;
	t_token	*sub_sequence;

	sub_sequence = NULL;
	commas = 0;
	components = components->next;
	while (components && handle_native_csg(prev, components->name) != SCOPE)
	{
		if (strcmp(components->name, ";") == 0)
		{
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
			//sub_sequence = arraypush(sub_sequence, components[counter]);
			sub_sequence = push_token(sub_sequence, 
				components->name, components->type, -1, 
				"thing");
		}
		prev = components->name;
		components = components->next;	
	}
	printf("EXITING for loop %s\n", components->name);
	if (commas > 2)
		printf("too many commas\n");
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



