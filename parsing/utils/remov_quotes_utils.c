/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remov_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:18:25 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/28 16:20:07 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rm_quotes(void)
{
	t_cmd_lexer	*cmd;

	cmd = *get_lexer_head(GET, NULL);
	while (cmd)
	{
		if (cmd->type == WORD)
			cmd->value = remov_quotes(cmd->value);
		cmd = cmd->next;
	}
}

void	mask_quotes(char **arg)
{
	int		i;
	char	c;
	char	s;

	i = 0;
	c = 0;
	while ((*arg)[i])
	{
		if (c == 0)
			if ((*arg)[i] == '\"' || (*arg)[i] == '\'')
			{
				c = (*arg)[i];
				if (c == '\'')
					s = -1;
				if (c == '\"')
					s = -3;
				(*arg)[i++] = s;
			}
		if ((*arg)[i] && (*arg)[i] == c)
		{
			(*arg)[i] = s;
			c = 0;
		}
		i++;
	}
}
