/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:20:16 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/02 10:23:23 by yel-ouam         ###   ########.fr       */
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
		printf("{cmd} -> [%s]\n", cmd->cmd);
		printf("{args} -> ");
		if (!cmd->args)
			printf("NULL\n");
		while (cmd->args[i])
			printf("[%s]", cmd->args[i++]);
		if (cmd->redirections)
		{
			printf("\n------->{redirctions}:\n");
			while (cmd->redirections)
			{
				printf("            ->[type]-> %d\n            ->[file/EOF]-> %s\n", cmd->redirections->type, cmd->redirections->value);
				cmd->redirections = cmd->redirections->next;
			}
		}
		printf("\n----------------------------------------\n");
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
	print_cmd_list();
	get_cmd_head(RESET, NULL);
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
			get_cmd_head(RESET, NULL);
			get_redi_head(RESET, NULL);
			break;
		}
		head = head->next;
	}
	get_syntax_head(RESET, NULL);
	get_cmd_head(RESET, NULL);
	get_redi_head(RESET, NULL);
}

void	minishell_loop(void)
{
	char		*line;

	while (1)
	{
		line = readline("Minishell > ");
		if (line != NULL && line[0] != '\0')
		{
			add_history(line);
			cmd_handling(line);
			free(line);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)envp;
	if (ac == 1)
	{
		minishell_loop();
	}
	else
	{
		printf("Error : minishell does not take arguments !!");
		return (1);
	}
	return (0);
}
