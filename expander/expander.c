/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:20:42 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/24 15:59:19 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_bool	varchr(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\'')
		return (false);
	while(s[i])
	{
		if (s[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char	*xpn_var(char *s)
{
	int		i;
	int		size;
	char	*var;

	i = 0;
	size = 0;
	while(s[i])
	{
		if(s[i] == '$')
		{
			i++;
			while (s[i] && s[i] != ' ' && ft_isprint(s[i]))
			{
				if (s[i] == '\'')
					break;
				i++;
				size++;
			}
			if (s[(i - 1)] == '\"')
			{
				i--;
				size--;
			}
			break ;
		}
		i++;
	}
	if (size == 0)
		return (NULL);
	var = ft_substr(s, i - size, size);
	return (var);
}

char	*is_expand(char *arg)
{
	int		i;
	int		t;
	char	*tmp;
	char	*var;

	i = 0;
	t = 0;
	tmp = NULL;
	var = NULL;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			tmp = ft_strjoin(tmp, ft_substr(arg, t, (i - t)));
			var = ft_strdup(xpn_var(arg + i));
			tmp = ft_strjoin(tmp, ft_getenv(var));
			i += ft_strlen(var);
			t = i + 1;
		}
		i++;
	}
	if (t != i + 1)
		tmp = ft_strjoin(tmp, ft_substr(arg, t, (i - t)));
	return(tmp);
}

char	*expander(char *args)
{
	int		i;
	int		t;
	char	*tmp;

	i = 0;
	t = 0;
	while (args[i])
	{
		if (args[i] == '\'')
		check_quotes(SET, args[i]);
		if(args[i] == '$' && (ft_isprint(args[i + 1]) || args[i + 1] == '$'))
		{
			if (!check_quotes(GET, 0))
			tmp = is_expand(args);
			t = 1;
		}
		i++;
	}
	if (t == 0)
	return(args);
	free(args);
	args = NULL;
	return(tmp);
}