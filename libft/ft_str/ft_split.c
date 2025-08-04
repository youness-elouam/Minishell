/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:41:39 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/27 18:41:25 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../includes/minishell.h"

static size_t	count_words(const char *str, char sep)
{
	size_t	count;
	int		in_word;
	size_t	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == sep)
		{
			in_word = 0;
		}
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_chek2free(char **p, size_t j)
{
	size_t	i;

	if (p[j] == NULL)
	{
		i = 0;
		while (i < j)
		{
			free(p[i]);
			i++;
		}
		free(p);
		return (1);
	}
	return (0);
}

char	**ft_fillwords(char **p, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		len = 0;
		while (s[i + len] && s[i + len] != c)
			len++;
		p[j] = ft_substr(s, i, len);
		if (ft_chek2free(p, j++))
			return (NULL);
		i += len;
	}
	p[j] = NULL;
	return (p);
}

char	**ft_split(const char *s, char c)
{
	char	**p;

	if (!s)
		return (NULL);
	p = (char **)ft_malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	p = ft_fillwords(p, s, c);
	if (!p)
		return (NULL);
	return (p);
}
