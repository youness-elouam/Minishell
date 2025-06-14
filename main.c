/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloukili <sloukili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:20:16 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/06/12 22:37:58 by sloukili         ###   ########.fr       */
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

t_bool	cmd_exec(t_syntax *cmd)
{
	cmd_lexer(cmd);
	if (!check_cmd_logic())
		return (false);
	print_cmd_data(cmd);
	get_lexer_head(RESET, NULL);
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

int	main()
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
	return (0);
}
