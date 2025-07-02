/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:50:20 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/06/28 16:55:38 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	check_quotes(t_method method, char value)
{
	static char	quote;

	if (method == GET)
	{
		if (quote == 0)
			return (false);
		return (true);
	}
	else if (method == SET)
	{
		if (quote != 0 && quote != value)
			return (true);
		if (quote == value)
			quote = 0;
		else
			quote = value;
	}
	else if (method == RESET)
		quote = 0;
	return (false);
}

void	syntax_error(char *error)
{
	printf("Error : %s\n", error);
	get_syntax_head(RESET, NULL);
	check_quotes(RESET, 0);
}

t_bool	check_syntax(void)
{
	t_syntax	*syntax;

	syntax = *get_syntax_head(GET, NULL);
	if (!syntax)
		return (true);
	if (check_quotes(GET, 0))
		return (syntax_error("error ched quotes!!"), false);
	while (syntax->next)
		syntax = syntax->next;
	if (syntax->type == PIPE || (*get_syntax_head(GET, NULL))->type == PIPE)
		return (syntax_error("error: SYNTAX PIPE ERROR!!"), false);
	return (true);
}
