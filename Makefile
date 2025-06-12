NAME = minishell

FILES = ./main.c

PARS = lexer/syntax_check.c lexer/syntax_list.c lexer/syntax_lexer.c lexer/cmd_list.c \
		utils/string.c lexer/cmd_lexer.c cmd.c lexer/redirections.c

OBJS = $(FILES:.c=.o)

PARS_OBJ = $(addprefix parsing/, $(PARS:.c=.o))

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(PARS_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(PARS_OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJS) $(PARS_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean

.SECONDARY: $(OBJS)