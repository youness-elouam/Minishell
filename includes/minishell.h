/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 04:07:40 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/02 10:29:47 by yel-ouam         ###   ########.fr       */
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
	struct s_cmd	*next;
}			t_cmd;

t_cmd			**get_cmd_head(t_method method, t_cmd *syntax);
void			add_cmd_node(t_cmd	**new_node);
t_redirections	**get_redi_head(t_method method, t_redirections *syntax);
void			add_redi_node(t_cmd_type type, char *value);
int				array_size(char **arr);
char			*ft_strdup(char *s);
void			free_array(char **arr);
char			**dc_array(char **arr, char *s);
void			cmd_list(t_cmd_lexer *cmd_lx);

#endif