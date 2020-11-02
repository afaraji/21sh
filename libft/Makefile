# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afaraji <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 16:52:07 by afaraji           #+#    #+#              #
#    Updated: 2018/10/08 14:59:46 by afaraji          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ./ft_atoi.c ./ft_bzero.c ./ft_ilen.c ./ft_isalnum.c ./ft_isalpha.c	\
	./ft_isascii.c ./ft_isdigit.c ./ft_isprint.c ./ft_isspace.c ./ft_itoa.c	\
	./ft_lstadd.c ./ft_lstdel.c ./ft_lstdelone.c ./ft_lstiter.c ./ft_lstmap.c\
	./ft_lstnew.c ./ft_memalloc.c ./ft_memccpy.c ./ft_memchr.c ./ft_memcmp.c\
	./ft_memcpy.c ./ft_memdel.c ./ft_memmove.c ./ft_memset.c ./ft_putchar.c	\
	./ft_putchar_fd.c ./ft_putendl.c ./ft_putendl_fd.c ./ft_putnbr.c		\
	./ft_putnbr_fd.c ./ft_putstr.c ./ft_putstr_fd.c ./ft_strcapitalize.c	\
	./ft_strcat.c ./ft_strchr.c ./ft_strclr.c ./ft_strcmp.c ./ft_strcpy.c	\
	./ft_strdel.c ./ft_strdup.c ./ft_strequ.c ./ft_striter.c ./ft_striteri.c\
	./ft_strjoin.c ./ft_strlcat.c ./ft_strlen.c ./ft_strlowcase.c ./ft_strmap.c\
	./ft_strmapi.c ./ft_strncat.c ./ft_strncmp.c ./ft_strncpy.c ./ft_strnequ.c\
	./ft_strnew.c ./ft_strnstr.c ./ft_strrchr.c ./ft_strsplit.c ./ft_strstr.c\
	./ft_strsub.c ./ft_strtrim.c ./ft_strupcase.c ./ft_tolower.c ./ft_toupper.c\
	./ft_word_len.c ./ft_words_count.c

INCLDS = ./libft.h

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@printf "making libft... "
	@gcc -Wall -Wextra -Werror -c $(SRC) -I $(INCLDS)
	@printf "done\n"
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

clean:
	@printf "removing OBJ files in ./libft/\n"
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@printf "removing libft.a\n"
	@/bin/rm -f $(NAME)

re: fclean all
