/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:09:50 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/27 20:11:04 by yel-ouam         ###   ########.fr       */
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
			if (tmp->args != NULL)
				ft_free(tmp->args);
			tmp->redirections = NULL;
			ft_free(tmp);
		}
	}
	return (&head);
}

void	add_cmd_node(t_cmd	**new_node)
{
	t_cmd	**head;
	t_cmd	*tmp;

	head = get_cmd_head(GET, NULL);
	tmp = *head;
	(*new_node) = ft_malloc(sizeof(t_cmd));
	(*new_node)->cmd = NULL;
	(*new_node)->args = NULL;
	(*new_node)->redirections = NULL;
	(*new_node)->next = NULL;
	if (head == NULL || *head == NULL)
		get_cmd_head(SET, *new_node);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *new_node;
	}
}

void	cmd_list(t_cmd_lexer *cmd_lx)
{
	t_cmd	*cmd;
	int		first_arg;

	first_arg = 0;
	add_cmd_node(&cmd);
	while (cmd_lx)
	{
		if (cmd_lx->type != WORD)
		{
			add_redi_node(cmd_lx->type, cmd_lx->next->value);
			if (cmd->redirections == NULL)
				cmd->redirections = *get_redi_head(GET, NULL);
			cmd_lx = cmd_lx->next->next;
		}
		if (cmd_lx != NULL && cmd_lx->type == WORD)
		{
			if (first_arg == 0)
			{
				cmd->cmd = ft_strdup(cmd_lx->value);
				first_arg = 1;
			}
			cmd->args = dc_array(cmd->args, cmd_lx->value);
			cmd_lx = cmd_lx->next;
		}
	}
}
