
#include "../inc/compiler.h"
#include "../inc/semantic.h"


#define FUNCTION 1
#define WHILE 2
#define IF 3
#define FOR 4
#define DO 5
/*
typedef struct	s_sstack
{
	int	scope_name;
	struct s_sstack	*next;
	struct s_sstack	*prev;
}	t_stack;
*/
t_stack		*new_stack(int scope_name)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	new->scope_name = scope_name;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_stack		*add_stack(t_stack *head, int scope_name)
{
	t_stack	*trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_stack(scope_name);
	trav->next->prev = trav;
	trav = trav->next;
	return (trav);
}

t_stack		*push_stack(t_stack *head, int scope_name)
{
	t_stack	*trav;

	trav = head;
	if (trav == NULL)
	{
		trav = new_stack(scope_name);
	}
	else
	{
		trav = add_stack(head, scope_name);
	}
	return (trav);
}

t_stack		*pop_stack(t_stack *current)
{
	t_stack	*trav;

	trav = current;
	current = current->prev;
	free(trav);
	return (current);
}

/*
int	main(void)
{
	t_stack *stack = NULL;

	stack = push_stack(stack, FUNCTION);
	stack = push_stack(stack, DO);
	stack = push_stack(stack, FOR);
	
	printf("stack value is %d\n", stack->scope_name);
	stack = pop_stack(stack);
	printf("stack is now %d\n", stack->scope_name);
	return (0);
} */





































