/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:58:51 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/17 09:21:42 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*find_var(t_env *env, const char *arg)
{
	char	*var_name;
	char	*env_name;

	var_name = malloc(g_n.buff_size);
	env_name = malloc(g_n.buff_size);
	if (!var_name || !env_name)
		return (NULL);
	get_env_name(var_name, arg);
	while (env)
	{
		if (env->value)
		{
			get_env_name(env_name, env->value);
			if (ft_strcmp(var_name, env_name) == 0)
			{
				free(var_name);
				free(env_name);
				return (env);
			}
		}
		env = env->next;
	}
	free(var_name);
	free(env_name);
	return (NULL);
}

static int	update_env_value(t_env *env, const char *arg, char *var_name,
		char *env_name)
{
	ft_memdel(env->value);
	env->value = ft_strdup(arg);
	free(var_name);
	free(env_name);
	return (1);
}

int	change_value(t_env *env, const char *arg)
{
	char	*var_name;
	char	*env_name;

	var_name = malloc(g_n.buff_size);
	env_name = malloc(g_n.buff_size);
	if (!var_name || !env_name)
		return (1);
	get_env_name(var_name, arg);
	while (env)
	{
		if (env->value)
		{
			get_env_name(env_name, env->value);
			if (ft_strcmp(var_name, env_name) == 0)
				return (update_env_value(env, arg, var_name, env_name));
		}
		env = env->next;
	}
	free(var_name);
	free(env_name);
	return (0);
}

int	is_var_exist(t_env *env, const char *arg)
{
	char	*var_name;
	char	*env_name;

	var_name = malloc(g_n.buff_size);
	env_name = malloc(g_n.buff_size);
	if (!var_name || !env_name)
		return (1);
	get_env_name(var_name, arg);
	while (env)
	{
		if (env->value)
		{
			get_env_name(env_name, env->value);
			if (ft_strcmp(var_name, env_name) == 0)
			{
				free(var_name);
				free(env_name);
				return (1);
			}
		}
		env = env->next;
	}
	free(var_name);
	free(env_name);
	return (0);
}

int	is_in_env(t_env *env, char *args)
{
	char	*var_name;
	char	*env_name;

	var_name = malloc(g_n.buff_size);
	env_name = malloc(g_n.buff_size);
	if (!var_name || !env_name)
		return (1);
	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			free(var_name);
			free(env_name);
			return (1);
		}
		env = env->next;
	}
	free(var_name);
	free(env_name);
	return (g_n.success);
}
