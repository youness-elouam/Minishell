/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:04:38 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/27 03:03:22 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	malloc_panic(void)
{
	printf("Malloc Failed: please buy some extra ram\n");
	exit(42);
}

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
				ft_free(tmp->ptr);
			ft_free(tmp);
		}
		return(NULL);
	}
	return (&head);
}

void	add_malloc_node(void *ptr)
{
	t_malloc	*new_node;
	t_malloc	**head;
	t_malloc	*tmp;

	if (!ptr)
		return ;
	head = get_malloc_head(GET, NULL);
	tmp = *head;
	new_node = malloc(sizeof(t_malloc));
	if (!new_node)
		malloc_panic();
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

	ptr = *get_malloc_head(GET, NULL);
	tmp = NULL;
	while (ptr)
	{
		if (ptr->ptr == s)
		{
			if (tmp == NULL)
				get_malloc_head(SET, ptr->next);
			else
				tmp->next = ptr->next;
			free (ptr->ptr);
			free (ptr);
			break ;
		}
		tmp = ptr;
		ptr = ptr->next;
	}
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		malloc_panic();
	add_malloc_node(ptr);
	return (ptr);
}
