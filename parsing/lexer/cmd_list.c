/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:08:07 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/26 13:01:44 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_lexer	**get_lexer_head(t_method method, t_cmd_lexer *syntax)
{
	static t_cmd_lexer	*head;
	t_cmd_lexer			*tmp;

	if (method == SET)
		head = syntax;
	else if (method == RESET)
	{
		while (head)
		{
			tmp = head;
			head = head->next;
			if (tmp->value != NULL)
			{
				ft_free(tmp->value);
				tmp->value = NULL;
			}
			ft_free(tmp);
		}
	}
	return (&head);
}

void	add_lexer_node(t_cmd_type type, char *value)
{
	t_cmd_lexer	*new_node;
	t_cmd_lexer	**head;
	t_cmd_lexer	*tmp;

	if (type == WORD && !value)
		return ;
	head = get_lexer_head(GET, NULL);
	tmp = *head;
	new_node = ft_malloc(sizeof(t_cmd_lexer));
	new_node->type = type;
	new_node->value = value;
	new_node->next = NULL;
	if (head == NULL || *head == NULL)
		get_lexer_head(SET, new_node);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	free_cmd_node(t_cmd *cmd)
{
	int				i;
	t_redirections	*tmp;

	i = -1;
	if (!cmd)
		return ;
	if (cmd->args != NULL)
	{
		while (cmd->args[++i])
			free(cmd->args[i]);
	}
	if (cmd->cmd != NULL)
		free(cmd->cmd);
	if (cmd->redirections)
	{
		while (cmd->redirections)
		{
			tmp = cmd->redirections;
			cmd->redirections = cmd->redirections->next;
			free(tmp->value);
			free(tmp);
		}
	}
}

//	t_cmd	**get_cmd_head(t_method method, t_cmd *syntax)
//	{
//		static t_cmd	*head;
//		t_cmd			*tmp;
//	
//		if (method == SET)
//			head = syntax;
//		else if (method == RESET)
//		{
//			while (head)
//			{
//				tmp = head;
//				head = head->next;
//				free_cmd_node(tmp);
//				free(tmp);
//			}
//		}
//		return (&head);
//	}
//	
//	t_cmd	*add_cmd_node(char *name)
//	{
//		t_cmd	*new_node;
//		t_cmd	**head;
//		t_cmd	*tmp;
//	
//		head = get_cmd_head(GET, NULL);
//		tmp = *head;
//		new_node = malloc(sizeof(t_cmd));
//		new_node->cmd = name;
//		new_node->args = NULL;
//		new_node->redirections = NULL;
//		new_node->path = NULL;
//		new_node->next = NULL;
//		if (head == NULL || *head == NULL)
//			get_cmd_head(SET, new_node);
//		else
//		{
//			while (tmp->next)
//				tmp = tmp->next;
//			tmp->next = new_node;
//		}
//		return (new_node);
//	}
