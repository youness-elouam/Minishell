/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:09:50 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/06/25 10:06:40 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	**get_cmd_head(t_method method, t_cmd *syntax)
{
	static t_cmd	*head;
	t_cmd			*tmp;

	if (method == SET)
		head = syntax;
	else if (method == RESET)
	{
		while (head)
		{
			tmp = head;
			head = head->next;
			if (tmp->cmd != NULL)
				ft_free(tmp->cmd);
			ft_free(tmp);
		}
	}
	return (&head);
}

void	add_cmd_node(t_cmd_type type, char *value)
{
	t_cmd	*new_node;
	t_cmd	**head;
	t_cmd	*tmp;

	if (type == WORD && !value)
		return ;
	head = get_cmd_head(GET, NULL);
	tmp = *head;
	new_node = ft_malloc(sizeof(t_cmd));
	new_node->cmd = NULL;
	new_node->args = NULL;
	new_node->redirections = NULL;
	new_node->path = NULL;
	new_node->next = NULL;
	if (head == NULL || *head == NULL)
		get_cmd_head(SET, new_node);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	cmd(t_cmd_lexer *cmd_list)
{
	while (cmd_list)
	{
		if(cmd_list->type == WORD)
		{

		}
	}

}
