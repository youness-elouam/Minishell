/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:40:28 by ael-boul          #+#    #+#             */
/*   Updated: 2025/08/08 16:30:17 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_and_update_pipe(int *prev_pipe, int *pipefd, int has_next)
{
	printf("--------------------%d\n", *prev_pipe);
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
	if (info.prev_pipe != -1)
	{
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

	if (cmd->args && is_dir(cmd->args[0]))
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		mini->ret = 126;
		return ;
	}
	setup_pipes_and_redirs(cmd, mini, info);
	if (cmd->cmd)
		path = get_cmd_path(cmd->args[0], mini->env);
	else
	{
		get_malloc_head(RESET, NULL);
		exit(0) ;
	}
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd->args, mini));
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		get_malloc_head(RESET, NULL);
		mini->ret = 127;
		exit(0) ;
	}
	magic_box(path, cmd, mini->env);
	get_malloc_head(RESET, NULL);
	exit(0) ;
}
