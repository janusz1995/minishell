
.PHONY: all re fclean clean

NAME = minishell

<<<<<<< HEAD:drina/Makefile1
<<<<<<< HEAD:drina/Makefile
SRC = minishell.c add_back.c lstnew.c all_envp.c add_equal.c get_home_dir.c sort_list.c \
		cmd_pwd.c cmd_env.c
=======
SRC = minishell.c add_back.c lstnew.c lst_args.c parser.c read_arg.c enter_cd.c
>>>>>>> lmidori:Makefile
=======
SRC = minishell.c add_back.c lstnew.c lst_args.c parser.c read_arg.c enter_cd.c parser4.c
>>>>>>> lmidori:lmidori/Makefile

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
