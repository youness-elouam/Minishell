/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:50:57 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/17 09:21:56 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	env_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_env *env)
{
	if (!env)
		return ;
	if (env->value)
		ft_memdel(env->value);
	ft_memdel(env);
}

static int	unset_head(char *key, t_env **env_ptr)
{
	t_env	*env;

	if (!key || !env_ptr || !*env_ptr)
		return (g_n.success);
	env = *env_ptr;
	if (env->value && ft_strncmp(key, env->value, env_size(env->value)) == 0
		&& key[env_size(env->value)] == '\0')
	{
		*env_ptr = env->next;
		free_node(env);
		return (g_n.success);
	}
	return (-1);
}

int	ft_unset_from_env(char *key, t_env **env_ptr)
{
	t_env	*env;
	t_env	*tmp;

	if (unset_head(key, env_ptr) == g_n.success)
		return (g_n.success);
	env = *env_ptr;
	while (env && env->next)
	{
		if (env->next->value && ft_strncmp(key, env->next->value,
				env_size(env->next->value)) == 0
			&& key[env_size(env->next->value)] == '\0')
		{
			tmp = env->next->next;
			free_node(env->next);
			env->next = tmp;
			break ;
		}
		env = env->next;
	}
	return (g_n.success);
}

int	ft_unset(char **args, t_mini *mini)
{
	int		i;

	if (!args[1])
		return (g_n.success);
	i = 1;
	while (args[i])
	{
		ft_unset_from_env(args[i], &(mini->env));
		ft_unset_from_env(args[i], &(mini->secret_env));
		i++;
	}
	return (g_n.success);
}
