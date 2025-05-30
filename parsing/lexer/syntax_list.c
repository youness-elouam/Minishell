/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 02:04:49 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/05/30 02:06:10 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_syntax	**get_syntax_head(t_method method, t_syntax *syntax)
{
	static t_syntax	*head;
	t_syntax		*tmp;

	if (method == SET)
		head = syntax;
	else if (method == RESET)
	{
		while (head)
		{
			tmp = head;
			head = head->next;
			if (tmp->value != NULL)
				free(tmp->value);
			free(tmp);
		}
	}
	return (&head);
}

void	add_syntax_node(t_syntax_type type, char *value)
{
	t_syntax	*new_node;
	t_syntax	**head;
	t_syntax	*tmp;

	if (type == CMD && !value)
		return ;
	head = get_syntax_head(GET, NULL);
	tmp = *head;
	new_node = malloc(sizeof(t_syntax));
	new_node->type = type;
	new_node->value = value;
	new_node->next = NULL;
	if (head == NULL || *head == NULL)
		get_syntax_head(SET, new_node);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}
