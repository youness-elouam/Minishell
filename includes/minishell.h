/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 04:07:40 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/26 21:33:11 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "exec.h"
# include "parsing.h"
# include "ft_malloc.h"
# include <readline/readline.h>
# include <readline/history.h>

extern char	**environ;

t_cmd			**get_cmd_head(t_method method, t_cmd *syntax);
void			add_cmd_node(t_cmd	**new_node);
t_redirections	**get_redi_head(t_method method, t_redirections *syntax);
void			add_redi_node(t_cmd_type type, char *value);
int				array_size(char **arr);
//char			*ft_strdup(char *s);
void			free_array(char **arr);
char			**dc_array(char **arr, char *s);
void			cmd_list(t_cmd_lexer *cmd_lx);
int				n_node(t_env *env);
char			**env_list_to_array(t_env *env);
char			*ft_getenv(const char *name);
int				expander(char **args);
void			fd_reset(t_method method);

#endif