
.PHONY: all re fclean clean

NAME = minishell

SRC = minishell.c lst_args.c read_arg.c init_arg_env.c \
        find_len_arg.c struct_funcs.c get_env_args.c parser.c path_bin.c cmd_cd.c \
        start_programm.c select_cmd.c diff_cmd.c print_export.c redact_env.c \
        lst_env.c find_in_env.c check.c cmd_unset.c get_value_env.c get_name_env.c \
        cmd_echo.c get_arg.c cmd_export.c xmalloc.c cmd_exit.c \
        add_new_env.c cmd_pwd.c cmd_env.c start_errors.c double_spec.c \
        special_parser.c free_list_copy.c redirect.c cmd_pipe.c error_and_free.c \
        last_spec.c commands.c start_programm_pipe.c \

SRCO = $(SRC:.c=.o)

CC = gcc -Wall -Werror -Wextra

LIBFT = $(LIBFTDIR)libft.a

LIBFTDIR = ../libft/

HEADER = minishell.h

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCO) $(LIBFT)
	$(CC) -L$(LIBFTDIR) -lft $(SRCO) -o $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(SRCO) $(SRCDRINAO)
	make clean -C $(LIBFTDIR)

fclean:
	rm -f $(SRCO) $(SRCDRINAO)
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all
