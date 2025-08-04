/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:20:16 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/27 16:14:07 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void print_cmd_data()
{
	t_cmd_lexer *cmd_lexer = *get_lexer_head(GET, NULL);
	if (!cmd_lexer)
	{
		puts("Cant parse the cmd");
		return ;
	}
	while (cmd_lexer)
	{
		if (cmd_lexer->type == R_APPEND)
			printf("{APPEND}[>>]\n");
		else if (cmd_lexer->type == R_HEREDOC)
			printf("{HEREDOC}[<<]\n");
		else if (cmd_lexer->type == R_IN)
			printf("{INFILE}[<]\n");
		else if (cmd_lexer->type == R_OUT)
			printf("{OUTFILE}[>]\n");
		else if (cmd_lexer->type == WORD)
			printf("{WORD}[%s]\n", cmd_lexer->value);
		cmd_lexer = cmd_lexer->next;
	}
	
	get_lexer_head(RESET, NULL);
}

void print_cmd_list()
{
	t_cmd	*cmd = *get_cmd_head(GET, NULL);
	int		i;

	i = 0;
	if (!cmd)
	{
		puts("Cant parse the cmd");
		return ;
	}
	while (cmd)
	{
		printf("\n----------------------------------------\n");
		printf("{cmd} -> [%s]\n", cmd->cmd);
		printf("{args} -> ");
		if (!cmd->args)
			printf("NULL\n");
		while (cmd->args[i])
			printf("[%s]", cmd->args[i++]);
		printf("\n");
		if (cmd->redirections)
		{
			printf("------->{redirctions}:\n");
			while (cmd->redirections)
			{
				printf("            ->[type]-> %d\n            ->[file/EOF]-> %s\n", cmd->redirections->type, cmd->redirections->value);
				cmd->redirections = cmd->redirections->next;
			}
		}
		printf("----------------------------------------\n");
		cmd = cmd->next;
	}
	
	get_lexer_head(RESET, NULL);
}

t_bool	cmd_exec(t_syntax *cmd)
{
	cmd_lexer(cmd);
	if (!check_cmd_logic())
		return (false);
	cmd_list(*get_lexer_head(GET, NULL));
	get_lexer_head(RESET, NULL);
	//print_cmd_list();
	//get_cmd_head(RESET, NULL);
	return (true);
}

void	cmd_handling(char *line)
{
	t_syntax	*head;

	syntax_lexer(line);
	if (!check_syntax())
		return ;
	head = *get_syntax_head(GET, NULL);
	while (head)
	{
		if (head->type != PIPE && !cmd_exec(head))
		{
			get_lexer_head(RESET, NULL);
			get_syntax_head(RESET, NULL);
			break;
		}
		head = head->next;
	}
	get_syntax_head(RESET, NULL);
}

static void	exec_one_cmd(t_cmd *cmd, t_mini *mini,
	int prev_pipe, int has_next)
{
	int			pipefd[2];
	pid_t		pid;
	t_exec_info	info;

	if (has_next && pipe(pipefd) == -1)
		return (perror("pipe"), (void)0);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), (void)0);
	if (pid == 0)
	{
		info.prev_pipe = prev_pipe;
		info.has_next = has_next;
		info.pipefd = pipefd;
		exec_child(cmd, mini, info);
	}
	waitpid(pid, &mini->status, 0);
	close_and_update_pipe(&prev_pipe, pipefd, has_next);
}

void	exec_pipeline(t_mini *mini)
{
	t_cmd	*cmd;
	int		prev_pipe;
	int		has_next;

	cmd = mini->start_cmd;
	prev_pipe = -1;
	while (cmd)
	{
		has_next = (cmd->next != NULL);
		exec_one_cmd(cmd, mini, prev_pipe, has_next);
		if (has_next)
			prev_pipe = mini->pipe_read;
		else
			prev_pipe = -1;
		cmd = cmd->next;
	}
}

int	minishell(t_mini *mini)
{
	mini->parent = 1;
	if (mini->start_cmd && !mini->start_cmd->next
		&& is_builtin(mini->start_cmd->args[0]))
	{
		fd_reset(SET);
		if (handle_redirs(mini->start_cmd->redirections, mini) == 0)
			mini->ret = exec_builtin(mini->start_cmd->args, mini);
		fd_reset(RESET);
	}
	else
	{
		exec_pipeline(mini);
	}
	if (mini->parent == 0)
	{
		free_cmd(mini->start_cmd);
		exit(mini->ret);
	}
	mini->no_exec = 0;
	return (mini->ret);
}

int	minishell_loop(char **env)
{
	char		*line;
	t_mini		mini;

	mini.exit = 0;
	mini.ret = 0;
	mini.no_exec = 0;
	env_init(&mini, env);
	secret_env_init(&mini, env);
	while (1)
	{
		line = readline("Minishell > ");
		if (line != NULL && line[0] != '\0')
		{
			g_n.my_env = env_list_to_array(mini.env);
			add_history(line);
			cmd_handling(line);
			mini.start_cmd = *get_cmd_head(GET, NULL);
			if (mini.start_cmd != NULL && mini.start_cmd->cmd)
				minishell(&mini);
			//print_cmd_list();
			free_array(g_n.my_env);
			get_cmd_head(RESET, NULL);
			get_redi_head(RESET, NULL);
			get_malloc_head(RESET, NULL);
			free(line);
		}
	}
	free_env(mini.env);
	free_env(mini.secret_env);
	return (mini.ret);
}

int	main(int ac, char **av, char **env)
{
	int	ret;

	(void)av;
	if (ac == 1)
	{
		ret = minishell_loop(env);
	}
	else
	{
		printf("Error : minishell does not take arguments !!");
		return (1);
	}
	return(ret);
}
