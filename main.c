/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:20:16 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/05/30 04:35:20 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main()
{
	char		*line;
	t_syntax	*head;

	while (1)
	{
		line = readline("Minishell > ");
		if (line[0] != '\0' && line != NULL)
			add_history(line);
		syntax_lexer(line);
		if (!check_syntax())
			return (1);
		head = *get_syntax_head(GET, NULL);
		while (head)
		{
			if (head->type == PIPE)
				puts("PIPE");
			else
				printf("-%s-\n", head->value);
			head = head->next;
		}
		get_syntax_head(RESET, NULL);
		free(line);
	}
	return (0);
}
