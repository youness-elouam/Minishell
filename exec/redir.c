/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:28 by ael-boul          #+#    #+#             */
/*   Updated: 2025/07/17 20:31:26 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	input(t_mini *mini, t_redirections *redir)
{
	if (!redir->value || redir->value[0] == '\0')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			g_n.stderr_fd);
		mini->ret = 1;
		mini->no_exec = 1;
		exit(1);
	}
	ft_close(mini->fdin);
	mini->fdin = open(redir->value, O_RDONLY);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", g_n.stderr_fd);
		ft_putstr_fd(redir->value, g_n.stderr_fd);
		ft_putendl_fd(": No ssdfuch file or directory", g_n.stderr_fd);
		mini->ret = 1;
		mini->no_exec = 1;
		exit(0);
	}
	dup2(mini->fdin, g_n.stdin_fd);
}

void	heredoc(t_mini *mini, t_redirections *redir)
{
	int		pipefd[2];
	char	*line;

	pipe(pipefd);
	mini->ret = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->value) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	handle_redirection(t_mini *mini, t_redirections *redir)
{
	int	fd;

	if (redir->type == R_OUT)
		fd = open(redir->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == R_APPEND)
		fd = open(redir->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		return ;
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->value, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		mini->ret = 1;
		mini->no_exec = 1;
		exit(0);
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(fd);
}

int	handle_redirs(t_redirections *redir, t_mini *mini)
{
	//save
	while (redir)
	{
		if (redir->type == R_OUT || redir->type == R_APPEND)
			handle_redirection(mini, redir);
		else if (redir->type == R_IN)
			input(mini, redir);
		else if (redir->type == R_HEREDOC)
			heredoc(mini, redir);
		redir = redir->next;
	}
	//restore
	return (0);
}
