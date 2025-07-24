/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:46:44 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/22 15:09:12 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**dc_array(char **arr, char *s)
{
	int		i;
	char	**new;

	i = 0;
	if (!s)
		return (arr);
	new = malloc(sizeof(char *) * (array_size(arr) + 2));
	if (!arr)
	{
		new[0] = ft_strdup(s);
		new[1] = NULL;
		return (new);
	}
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i++] = ft_strdup(s);
	new[i] = NULL;
	free_array(arr);
	return (new);
}
