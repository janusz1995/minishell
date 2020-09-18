
.PHONY: all re fclean clean

NAME = minishell

SRC = minishell.c add_back.c lstnew.c lst_args.c read_arg.c enter_cd.c init_arg_env.c \
find_len_arg.c struct_funcs.c get_env_args.c parser.c

SRCO = $(SRC:.c=.o)

CC = gcc

LIBFT = $(LIBFTDIR)libft.a

LIBFTDIR = ../libft/

HEADER = minishell.h

FLAGS = -g -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCO) $(LIBFT)
	$(CC) -g -L$(LIBFTDIR) -lft $(SRCO) -o $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(SRCO)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all
