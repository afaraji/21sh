# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 18:07:13 by afaraji           #+#    #+#              #
#    Updated: 2020/11/02 18:07:22 by afaraji          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
SRC_SHL = ./src/ast.c ./src/main.c ./src/manage_terminal.c ./src/readline.c	\
	./src/home_end.c ./src/go_right.c ./src/go_left.c ./src/copy.c ./src/cut.c\
	./src/past.c ./src/manage_newline.c ./src/join_line.c ./src/get_next_line.c\
	./src/manage_history.c ./src/navigate_history.c ./src/history_search.c	\
	./src/navigate_history_2.c ./src/move_by_word.c ./src/trim.c move_curs.c\
	./src/manage_line.c ./src/go_down.c ./src/go_up.c ./src/ft_strsplit_2.c	\
	./src/right_select.c ./src/left_select.c ./src/get_printable_char.c		\
	./src/get_unprintable_char.c ./src/builtins.c ./src/ft_cd_old.c			\
	./src/ft_cd_1.c ./src/ft_cd_2.c ./src/change_pwd.c ./src/ft_echo.c		\
	./src/verify_type.c ./src/setenv.c ./src/unsetenv.c ./src/export.c 		\
	./src/auto_complete.c ./src/io_redirect.c ./src/my_printf.c ./src/ft_free.c\
	./src/exec.c ./src/lexer.c

LIBFTA = ./libft/libft.a

SRC_LF = ./libft/ft_bzero.c ./libft/ft_isalnum.c ./libft/ft_isalpha.c	\
	./libft/ft_isdigit.c ./libft/ft_memalloc.c ./libft/ft_putstr.c	\
	./libft/ft_strcat.c ./libft/ft_strchr.c ./libft/ft_strcmp.c	\
	./libft/ft_strcpy.c ./libft/ft_strdup.c ./libft/ft_strjoin.c	\
	./libft/ft_strlen.c ./libft/ft_strnew.c	./libft/ft_strsplit.c	\
	./libft/ft_strsub.c

HEADER = ./inc/ast.h ./inc/builtins.h ./inc/exec.h ./inc/ft_21sh.h	\
	./inc/ft_free.h ./inc/parse.h ./inc/readline.h

OBJ_SHL = $(SRC_SHL:.c=.o)

OBJ_LF = $(SRC_LF:.c=.o)


all : $(NAME)

$(NAME) : $(OBJ_SHL) $(OBJ_LF)
	@$(MAKE) -C ./libft
	@gcc -I=$(HEADR)  $(SRC_SHL) $(LIBFTA) -ltermcap -o $(NAME)

clean :
	@printf "removing OBJ files\n"
	@/bin/rm -f $(OBJ_SHL)
	@$(MAKE) -C ./libft/ clean

fclean : clean
	@printf "removing executable\n"
	@/bin/rm -f $(NAME)
	@$(MAKE) -C ./libft/ fclean

re : fclean all
