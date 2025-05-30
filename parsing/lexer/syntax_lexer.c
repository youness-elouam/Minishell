/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:58:54 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/05/30 00:22:39 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_syntax_cmd(char *str, int start, int end)
{
	int		size;
	int		i;
	char	*cmd;

	size = end - start + 2;
	if (size - 2 < 0)
		return (NULL);
	cmd = malloc(sizeof(char) * size);
	i = 0;
	while (start <= end)
	{
		cmd[i] = str[start];
		start++;
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

void	syntax_lexer(char *syntax)
{
	int	cmd_start;
	int	i;

	cmd_start = 0;
	i = 0;
	while (syntax[i])
	{
		if (syntax[i] == '"' || syntax[i] == '\'')
			check_quotes(SET, syntax[i]);
		else if (syntax[i] == '|' && !check_quotes(GET, 0))
		{
			add_syntax_node(CMD, get_syntax_cmd(syntax, cmd_start, i - 1));
			add_syntax_node(PIPE, NULL);
			cmd_start = i + 1;
		}
		i++;
	}
	if (cmd_start < i)
		add_syntax_node(CMD, get_syntax_cmd(syntax, cmd_start, i - 1));
}
