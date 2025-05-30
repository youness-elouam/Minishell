/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 04:15:08 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/05/30 04:16:09 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum s_syntax_type
{
	CMD,
	PIPE
}	t_syntax_type;

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef enum s_method
{
	SET,
	GET,
	RESET
}	t_method;

typedef struct s_syntax
{
	t_syntax_type	type;
	char			*value;
	struct s_syntax	*next;
}	t_syntax;

// LEXER
t_syntax	**get_syntax_head(t_method method, t_syntax *syntax);
void		add_syntax_node(t_syntax_type type, char *value);
t_bool		check_quotes(t_method method, char value);
t_bool		check_syntax(void);
void		syntax_lexer(char *syntax);

#endif
