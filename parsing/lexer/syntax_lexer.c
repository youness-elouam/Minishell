/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:58:54 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/15 16:26:56 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_lexer(char *syntax)
{
	int	cmd_start;
	int	i;

	cmd_start = 0;
	i = 0;
	if (!syntax)
		return ;
	while (syntax[i])
	{
		if (syntax[i] == '"' || syntax[i] == '\'')
			check_quotes(SET, syntax[i]);
		else if (syntax[i] == '|' && !check_quotes(GET, 0))
		{
			add_syntax_node(CMD, ft_nsubstr(syntax, cmd_start, i - 1));
			add_syntax_node(PIPE, NULL);
			cmd_start = i + 1;
		}
		i++;
	}
	if (cmd_start < i)
		add_syntax_node(CMD, ft_nsubstr(syntax, cmd_start, i - 1));
}
