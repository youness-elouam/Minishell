/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 04:15:08 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/07/16 16:12:18 by yel-ouam         ###   ########.fr       */
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

typedef enum s_cmd_type
{
	WORD,
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}			t_cmd_type;

typedef struct s_cmd_lexer
{
	t_cmd_type			type;
	char				*value;
	struct s_cmd_lexer	*next;
}			t_cmd_lexer;

typedef struct s_syntax
{
	t_syntax_type	type;
	char			*value;
	struct s_syntax	*next;
}	t_syntax;

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

// LEXER
t_syntax	**get_syntax_head(t_method method, t_syntax *syntax);
void		add_syntax_node(t_syntax_type type, char *value);
t_bool		check_quotes(t_method method, char value);
t_bool		check_syntax(void);
void		syntax_lexer(char *syntax);

t_cmd_lexer	**get_lexer_head(t_method method, t_cmd_lexer *syntax);
void		add_lexer_node(t_cmd_type type, char *value);
void		cmd_lexer(t_syntax *cmd);
t_bool		check_cmd_logic(void);

// Utils
char		*ft_nsubstr(char *str, int start, int end);
t_bool		is_space(char c);

#endif
