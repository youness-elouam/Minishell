#include "../includes/minishell.h"

t_malloc	**get_malloc_head(t_method	method, t_malloc *list)
{
	static t_malloc	*head;
	t_malloc		*tmp;

	if (method == SET)
		head = list;
	else if (method == RESET)
	{
		while (head)
		{
			tmp = head;
			head = head->next;
			if (tmp->ptr != NULL)
				free(tmp->ptr);
			free(tmp);
		}
	}
	return (&head)
}

t_malloc	add_malloc_node(void *ptr)
{
	t_malloc	*new_node;
	t_malloc	**head;
	t_malloc	*tmp;

	if (!ptr)
		return(NULL);
	head = get_malloc_head(GET, NULL);
	tmp = *head;
	new_node = malloc(sizeof(t_malloc));
	new_node->ptr = ptr;
	new_node->next = NULL;
	if (head == NULL || *head == NULL)
		get_malloc_head(SET, new_node);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	ft_free(void *s)
{
	t_malloc	*ptr;
	t_malloc	*tmp;

	ptr = get_malloc_head(GET,  NULL);
	while (ptr)
	{
		if (ptr->ptr == &s)
		{
			tmp = ptr;
			ptr->next = ptr->next->next;
			free (tmp);
			free (s);
		}
		ptr = ptr->next;
	}
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	add_malloc_node(ptr);
	return(ptr);
}
