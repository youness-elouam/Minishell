/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:21:01 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/17 09:21:36 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_error(int error, const char *arg)
{
	int	i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", g_n.stderr_fd);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", g_n.stderr_fd);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(g_n.stderr_fd, &arg[i], 1);
		i++;
	}
	write(g_n.stderr_fd, "\n", 1);
	return (g_n.stderr_fd);
}

int	env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (0);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

char	*get_env_name(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < (size_t)g_n.buff_size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	handle_export_var(t_env *env, t_env *secret, const char *arg)
{
	t_env	*new_var;

	if (is_var_exist(secret, arg))
		change_value(secret, arg);
	else
		env_add(arg, secret);
	if (is_var_exist(env, arg))
		change_value(env, arg);
	else
	{
		env_add(arg, env);
		new_var = find_var(env, arg);
		if (new_var)
			new_var->exported = 1;
	}
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	int	error_type;
	int	i;

	if (!args[1])
	{
		print_sorted_env(secret);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '=')
			return (print_error(-3, args[i]));
		error_type = is_valid_env(args[i]);
		if (error_type <= 0)
			return (print_error(error_type, args[i]));
		if (error_type == 1 || error_type == 2)
			handle_export_var(env, secret, args[i]);
		i++;
	}
	return (0);
}
