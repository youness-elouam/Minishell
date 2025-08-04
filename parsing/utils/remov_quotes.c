/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remov_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:50:52 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/31 16:46:06 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remov_quotes(char	*value)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = 0;
	while (value[i])
	{
		if (value[i] == -3 || value[i] == -1)
			c = value[i++];
		while (value[i] != c && value[i])
		{
			if (c == 0)
				if (value[i] == -3 || value[i] == -1)
					c = value[i++];
			if (value[i] != c && value[i])
				value[j++] = value[i++];
		}
		if (!value[i])
			break ;
		i++;
	}
	value[j] = '\0';
	return (value);
}
