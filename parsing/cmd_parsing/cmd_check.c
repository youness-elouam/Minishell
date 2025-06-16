/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:15:46 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/06/12 16:03:34 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	get_cmd_list(t_method method, t_cmd *list)
{
	static t_cmd	*head;
	t_cmd			*tmp;

	if (method == SET)
		head =	list;
	else if (method == RESET)
	{
		while (head)
		{
			tmp = head;
			head = head->next;
			if (tmp->value != NULL)
				free(tmp->value);
			free(tmp);
		}
	}
    return (&head);
}

int	cmd_num(char *str)
{
	int		i;
	int		n;
	char	c;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] != c && str[i])
				i++;
			i++;
		}
		else if (str[i] == ' ')
		{
			n++;
			while (str[i] == ' ' && str[i])
				i++;
		}
		else
			i++;
	}
	if (str[i - 1] != ' ')
		n++;
	return (n);
}

char	**spleet_cmd(char *str)
{
	int		i;
	int		j;
	char	**cmd;

	i = 0;
	j = 0;
	cmd = malloc(sizeof(char*) * cmd_num(str));
	while (str)
	{}
}

t_bool	check_redirecting(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i++] == '>')
		{
			
		}
	}
}

t_bool	cmd_check(t_method method)
{
	t_syntax	*syntax;
	t_cmd		cmd_list;
	t_cmd		*tmp;
	char		**cmd;

	syntax = get_syntax_head(GET, NULL);
	while (syntax)
	{
		if(syntax->type == CMD)
		{
			if (!check_redirecting(syntax->value))
				return (syntax_error("error redirection !!"), false);
		}
	}
	cmd_list = get_cmd_list(SET, cmd_list);
}

//	#include <stdio.h>
//	
//	int	main()
//	{
//		char str[100] = "cat -f dd \"you ness\" >> file";
//		
//		printf("\n\n\n ////////test//////// \n\n\n");
//		printf("\n\n\n str : %s \n\n\n", str);
//		printf("cmd num: %d\n", cmd_num(str));
//	
//	}