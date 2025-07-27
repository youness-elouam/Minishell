/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:01:46 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/26 16:10:21 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	n_node(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**env_list_to_array(t_env *env)
{
	char	**my_envi;
	int		i;

	i = 0;
	my_envi = ft_malloc(sizeof(char*) * (n_node(env) + 1));
	while (env)
	{
		my_envi[i] = ft_strdup(env->value);
		i++;
		env = env->next;
	}
	my_envi[i] = NULL;
	return (my_envi);
}

char	*ft_getenv(const char *name)
{
	char	*var;
	char	**tmp;

	if (name == NULL || name[0] == '\0')
		return (NULL);
	tmp = environ;
	environ = g_n.my_env;
	var = getenv(name);
	environ = tmp;
	if (var == NULL)
		return("\0");
	return (var);
}