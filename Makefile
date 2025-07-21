NAME = minishell

FILES = ./main.c ./utils/dynamic_array.c ./utils/dc_array_utils.c ./exec/path.c ./exec/bin.c ./exec/fd.c ./exec/free.c ./exec/global.c ./exec/redir.c ./exec/sort_env.c ./exec/exec_help.c ./exec/builtin.c \
        builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c \
		builtins/help_exp.c builtins/pwd.c builtins/unset.c expander/expander.c expander/ft_getenv.c

PARS = lexer/syntax_check.c lexer/syntax_list.c lexer/syntax_lexer.c lexer/cmd_list.c \
		utils/string.c lexer/cmd_lexer.c cmd.c lexer/redirections.c 

OBJS = $(FILES:.c=.o)

PARS_OBJ = $(addprefix parsing/, $(PARS:.c=.o))

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

LIBFT_DIR   = ./libft

LIBFT_A     = $(LIBFT_DIR)/libft.a

LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(PARS_OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(PARS_OBJ) $(LIBFT_A) -o $(NAME) $(LDFLAGS)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS) $(PARS_OBJ) $(LIBFT_DIR)/*/*.o

fclean: clean
	rm -rf $(NAME) $(LIBFT_A) 

re: fclean all

.PHONY: clean

.SECONDARY: $(OBJS)