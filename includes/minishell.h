/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 04:07:40 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/06/26 23:39:41 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "parsing.h"
# include "ft_malloc.h"
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_redirections
{
	t_cmd_type				type;
	char					*value;
	struct s_redirections	*next;
}			t_redirections;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redirections	*redirections;
	char			*path;
	struct s_cmd	*next;
}			t_cmd;

int		array_size(char **arr);
char	*ft_strdup(char *s);
void	free_array(char **arr);
int		args_num(void);


#endif