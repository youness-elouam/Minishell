/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:01:46 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/16 16:03:03 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_mini *mini)
{
	int	result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(mini, args);
	if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(mini->env);
	if (ft_strcmp(args[0], "export") == 0)
		result = ft_export(args, mini->env, mini->secret_env);
	if (ft_strcmp(args[0], "unset") == 0)
		result = ft_unset(args, mini);
	if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(mini, args);
	return (result);
}
