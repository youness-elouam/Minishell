/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:40:28 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/17 23:20:46 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_and_update_pipe(int *prev_pipe, int *pipefd, int has_next)
{
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (has_next)
	{
		close(pipefd[1]);
		*prev_pipe = pipefd[0];
	}
	else
		*prev_pipe = -1;
}

static void	setup_pipes_and_redirs(t_cmd *cmd, t_mini *mini, t_exec_info info)
{
	printf("///////////////////// fd1 = %d ////////////\n", info.prev_pipe);
	if (info.prev_pipe != -1)
	{
		printf("///////////////////// fd = %d ////////////\n", info.prev_pipe);
		dup2(info.prev_pipe, STDIN_FILENO);
		close(info.prev_pipe);
	}
	if (info.has_next)
	{
		close(info.pipefd[0]);
		dup2(info.pipefd[1], STDOUT_FILENO);
		close(info.pipefd[1]);
	}
	if (cmd->redirections)
		handle_redirs(cmd->redirections, mini);
}

 void	exec_child(t_cmd *cmd, t_mini *mini, t_exec_info info)
{
	char	*path;

	setup_pipes_and_redirs(cmd, mini, info);
	path = get_cmd_path(cmd->args[0], mini->env);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd->args, mini));
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		mini->ret = 127;
		exit(mini->ret);
	}
	magic_box(path, cmd, mini->env, mini);
	exit(1);
}
