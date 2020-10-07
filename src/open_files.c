
#include "../inc/compiler.h"


char	**new_line(char *content)
{
	char **array;
	char *str;
	int i;

	array = NULL;
	str = NULL;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
		{
			str = charpush(str, '\n');
			array = arraypush(array, str);
			free(str);
			str = NULL;
		}
		else
			str = charpush(str, content[i]);
		i++;
	}
	return (array);
}

t_file	*new_file(char *filename, char *file_content)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	new->filename = strdup(filename);
	new->content = new_line(file_content);
	new->solidcontent = strdup(file_content);
	new->next = NULL;
	return (new);
}

t_file	*add_file(t_file *head, char *filename, char *file_content)
{
	t_file	*trav;

	trav = head;
	while (trav->next)
		trav = trav->next;
	trav->next = new_file(filename, file_content);
	return (trav);
}

t_file	*push_file(t_file *head, char *filename, char *file_content)
{
	t_file 	*trav;
	
	trav = head;
	if (trav == NULL)
		trav = new_file(filename, file_content);
	else
	{
		trav = add_file(head, filename, file_content);
		trav = head;
	}
	return (trav);
}








