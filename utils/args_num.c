/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:21:37 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/06/26 23:46:47 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	args_num(void)
{
	t_cmd_lexer *cmd;
	int	n;
	int	r;

	n = 0;
	r = 0;
	cmd = *get_lexer_head(GET, NULL);
	while (cmd)
	{
		if(cmd->type != WORD)
			r++;
		n++;
		cmd = cmd->next;
	}
	return (n - (r * 2) - 1);
}