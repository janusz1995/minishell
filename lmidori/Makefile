
.PHONY: all re fclean clean

NAME = minishell

SRC = minishell.c add_back.c lstnew.c lst_args.c read_arg.c init_arg_env.c \
        find_len_arg.c struct_funcs.c get_env_args.c parser.c path_bin.c cmd_cd.c \
        start_programm.c select_cmd.c diff_cmd.c lst_env.c print_export.c redact_env.c \
        lst_new_env.c find_in_env.c check.c cmd_unset.c get_value_env.c get_name_env.c \
        cmd_echo.c init_env.c ft_lstsize_arg.c get_arg.c cmd_export.c

SRCDRINA = ../drina/add_equal.c ../drina/sort_list.c ../drina/cmd_pwd.c ../drina/cmd_env.c

SRCO = $(SRC:.c=.o)

SRCDRINAO = $(SRCDRINA:.c=.o)

CC = gcc

LIBFT = $(LIBFTDIR)libft.a

LIBFTDIR = ../libft/

HEADER = minishell.h

FLAGS = -g -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCO) $(LIBFT) $(SRCDRINAO)
	$(CC) -g -L$(LIBFTDIR) -lft $(SRCO) $(SRCDRINAO) -o $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(SRCO) $(SRCDRINAO)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all
