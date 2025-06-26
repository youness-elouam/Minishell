/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:46:44 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/06/26 22:46:22 by yel-ouam         ###   ########.fr       */
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

void	ft_strcpy(char *s1, char **s2)
{
	int	i;

	i = 0;
	if (!s1)
		return ;
	*s2 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	while(s1[i])
	{
		(*s2)[i] = s1[i];
		i++;
	}
	(*s2)[i] = '\0';
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
		ft_strcpy(arr[i], &(new[i]));
		i++;
	}
	ft_strcpy(s, &(new[i++]));
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
	ft_strcpy("youness", &arr[0]);
	ft_strcpy("Elouam", &arr[1]);
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