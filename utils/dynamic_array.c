/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloukili <sloukili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:46:44 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/06/26 22:52:15 by sloukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	array_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while(arr[i])
		i++;
	return(i);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return(0);
	while(s[i])
		i++;
	return(i);
}


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

char	*ft_strdup(char *s)
{
	size_t	len;
	char	*rs;

	len = ft_strlen(s);
	rs = (char *)malloc((len + 1) * sizeof(char));
	if (!rs)
		return (NULL);
	ft_strcpy(rs, s);
	return (rs);
}

void	free_array(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**dc_array(char **arr, char *s)
{
	int	i;
	char	**new;
	
	i = 0;
	if (!arr)
		return(NULL);
	new = malloc(sizeof(char*) * (array_size(arr) + 2));
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

int	main()
{
	int	i;
	char **arr;
	
	i = 0;
	arr = malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("youness");
	arr[1] = ft_strdup("Elouam");
	arr[2] = NULL;
	while(arr[i])
	{
		printf("arr1 = %s\n", arr[i]);
		i++;
	}
	arr = dc_array(arr, "1337");
	arr = dc_array(arr, "1111111111");
	arr = dc_array(arr, NULL);
	i = 0;
	printf("///////\n");
	while(arr[i])
		printf("arr2 = %s\n", arr[i++]);
	free_array(arr);
	
}