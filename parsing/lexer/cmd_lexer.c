/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:13:19 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/27 01:12:18 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_type	get_lexer_type(char *cmd)
{
	if (!cmd || !cmd[0])
		return (WORD);
	if (cmd[0] == '<' && cmd[1] == '<')
		return (R_HEREDOC);
	if (cmd[0] == '>' && cmd[1] == '>')
		return (R_APPEND);
	if (cmd[0] == '<')
		return (R_IN);
	if (cmd[0] == '>')
		return (R_OUT);
	return (WORD);
}

// ls > < sq

void	unexpected_redirection(t_cmd_type type)
{
	if (type == R_APPEND)
		printf("Error: unexpected redirection at >>\n");
	else if (type == R_HEREDOC)
		printf("Error: unexpected redirection at <<\n");
	else if (type == R_IN)
		printf("Error: unexpected redirection at <\n");
	else if (type == R_OUT)
		printf("Error: unexpected redirection at >\n");
}

t_bool	check_cmd_logic(void)
{
	t_cmd_lexer	*cmd;
	t_cmd_type	old;

	old = WORD;
	cmd = *get_lexer_head(GET, NULL);
	while (cmd)
	{
		if (old != WORD && cmd->type != WORD)
		{
			unexpected_redirection(cmd->type);
			return (false);
		}
		if (!cmd->next && cmd->type != WORD)
		{
			printf("Error: Cmd end with a redirection\n");
			return (false);
		}
		old = cmd->type;
		cmd = cmd->next;
	}
	return (true);
}

void	rm_quotes(void)
{
	t_cmd_lexer *cmd;

	cmd = *get_lexer_head(GET, NULL);
	while(cmd)
	{
		cmd->value = remov_quotes(cmd->value);
		cmd = cmd->next;
	}
}

void	mask_quotes(char **arg)
{
	int		i;
	char	c;
	char	s;

	i = 0;
	c = 0;
	while((*arg)[i])
	{
		if(c == 0)
			if ((*arg)[i] == '\"' || (*arg)[i] == '\'')
			{
				c = (*arg)[i];
				if (c == '\'')
					s = -1;
				if (c == '\"')
					s = -3;
			}
		if((*arg)[i] == c)
			(*arg)[i] = s;
		i++;
	}
}

void	cmd_lexer(t_syntax *cmd)
{
	int			cmd_start;
	int			i;
	t_cmd_type	r_type;

	cmd_start = 0;
	i = 0;
	mask_quotes(&cmd->value);
	expander(&cmd->value);
	check_quotes(RESET, 0);
	while (cmd->value[i])
	{
		r_type = get_lexer_type(&(cmd->value[i]));
		if (cmd->value[i] == '"' || cmd->value[i] == '\'' || cmd->value[i] == -3 || cmd->value[i] == -1)
			check_quotes(SET, cmd->value[i]);
		else if (is_space(cmd->value[i]) && !check_quotes(GET, 0))
		{
			add_lexer_node(WORD, ft_nsubstr(cmd->value, cmd_start, i - 1));
			cmd_start = i + 1;
		}
		else if (r_type != WORD && !check_quotes(GET, 0))
		{
			add_lexer_node(WORD, ft_nsubstr(cmd->value, cmd_start, i - 1));
			add_lexer_node(r_type, NULL);
			if (r_type == R_HEREDOC || r_type == R_APPEND)
				i++;
			cmd_start = i + 1;
		}
		i++;
	}
	if (cmd_start < i)
		add_lexer_node(WORD, ft_nsubstr(cmd->value, cmd_start, i - 1));
	rm_quotes();
}
