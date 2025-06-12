/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloukili <sloukili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 04:07:40 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/06/12 22:09:15 by sloukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "parsing.h"
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

#endif