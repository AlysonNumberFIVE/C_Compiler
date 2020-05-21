

#include "../inc/compiler.h"

typedef struct s_test
{
    int digit;
    struct s_test *next;
}   t_test;

t_test      *new_test(int i)
{
    t_test  *head;

    head = (t_test *)malloc(sizeof(t_test));
    head->digit = i;
    head->next = NULL;
    return (head);
}

t_test      *add_test(t_test *head, int i)
{
    t_test  *trav;

    trav = head;
    while (trav->next)
        trav = trav->next;
    trav->next = (t_test *)malloc(sizeof(t_test));
    trav->next->digit = i;
    trav->next->next = NULL;
    return (trav);
}

t_test      *push_test(t_test *head, int i)
{
    t_test  *trav;

    trav = head;
    if (trav == NULL)
    {
        head = new_test(i);
    }
    else
    {
        trav = add_test(head, i);
        trav = head;
    }
    return (head);
}


t_test    *delete_from_index(t_test *first, int index)
{
    int i;
    t_test *trav;
    t_test  *delete;
    t_test  *temp;

    i = 0;
    trav = first;
    while (trav)
    {
        if (i == index)
            break;
        trav = trav->next;
        i++;
    }
    delete = trav;
    trav->next = NULL;
    while (delete)
    {
        printf("delete : %d\n", delete->digit);
        temp = delete;
        delete = delete->next;
        free(temp);
        temp = NULL;
    }
    return (first);
}

t_test    *merge_inherited_symbols(t_test *first, t_test *second)
{
    t_test *head;
    t_test *trav;

    head = first;
    trav = first;
    while (trav->next)
        trav = trav->next;
    trav->next = second;
    return (first);
}

void    print_test(t_test *head)
{
    t_test  *trav;
    int counter=  0;
    trav = head;
    while (trav)
    {
        printf("%d\n", trav->digit);
        trav = trav->next;
        counter++;
    }
    printf("total  ; %d\n", counter);
    printf("\n");
}

int     main(void)
{
    t_test  *first;
    t_test  *second;
    t_test  *third;

    first = NULL;
    second = NULL;
    first = push_test(first, 1);
    first = push_test(first, 2);
    first = push_test(first, 3);


    second = push_test(second, 4);
    second = push_test(second, 5);
    second = push_test(second, 6);

    third = push_test(third, 7);
    third = push_test(third, 8);
    third = push_test(third, 9);

    first = merge_inherited_symbols(first, second);
    print_test(first);
    first = merge_inherited_symbols(first, third);
    print_test(first);
    printf("\n\n");
    first = delete_from_index(first, 5);
    print_test(first);
    first = delete_from_index(first, 2);
    print_test(first);
    return (0);
}
