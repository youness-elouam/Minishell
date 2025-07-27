/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:21:43 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/26 16:22:44 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exit_too_many_args(t_mini *mini)
{
	mini->ret = 1;
	ft_putendl_fd("minishell: exit: too many arguments", g_n.stderr_fd);
	return (1);
}

static void	exit_numeric_error(t_mini *mini, char *arg)
{
	mini->ret = 2;
	ft_putstr_fd("minishell: exit: ", g_n.stderr_fd);
	ft_putstr_fd(arg, g_n.stderr_fd);
	ft_putendl_fd(": numeric argument required", g_n.stderr_fd);
	exit(mini->ret);
}

void	ft_exit(t_mini *mini, char **cmd)
{
	int	status;

	ft_putstr_fd("exit\n", g_n.stderr_fd);
	if (cmd[1] && cmd[2])
	{
		if (exit_too_many_args(mini))
			return ;
	}
	if (cmd[1])
	{
		if (ft_strisnum(cmd[1]) == 0)
			exit_numeric_error(mini, cmd[1]);
		status = ft_atoi(cmd[1]) % 256;
	}
	else
		status = 0;
	mini->ret = status;
	free_env(mini->env);
	free_env(mini->secret_env);
	get_cmd_head(RESET, NULL);
	get_redi_head(RESET, NULL);
	get_malloc_head(RESET, NULL);
	exit(mini->ret);
}
