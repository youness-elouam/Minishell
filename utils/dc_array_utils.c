/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_array_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:10:46 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/23 19:01:09 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	array_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !arr[i])
		return (0);
	while (arr[i])
		i++;
	return (i);
}

//	size_t	ft_strlen(char *s)
//	{
//		size_t	i;
//	
//		i = 0;
//		if (!s)
//			return (0);
//		while (s[i])
//			i++;
//		return (i);
//	}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

// char	*ft_strdup(char *s)
// {
// 	size_t	len;
// 	char	*rs;
// 
// 	len = ft_strlen(s);
// 	rs = malloc((len + 1) * sizeof(char));
// 	if (!rs)
// 		return (NULL);
// 	ft_strcpy(rs, s);
// 	return (rs);
// }

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
}
