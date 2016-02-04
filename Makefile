#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/11 14:41:25 by cwagner           #+#    #+#              #
#    Updated: 2014/03/18 18:54:22 by cwagner          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror -g
INCLUDES =	-I includes/
SRCDIR =	srcs/
SRCFILES =	main.c\
			error.c\
			acquisition.c\
			parsing.c\
			solving.c
SRCS =		$(addprefix $(SRCDIR), $(SRCFILES))
OBJ =		$(SRCS:.c=.o)
LIB =		-L libft/ -lft
NAME = 		./lem-in

all: $(NAME) clean

$(NAME): make $(OBJ)
	@echo "\033[32m[Building] \033[0m" | tr -d '\n'
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(INCLUDES)

make:
	@echo "\033[31m[Libft] \033[0m" | tr -d '\n'
	make -C libft/

remake:
	@echo "\033[31m[Re-Libft] \033[0m" | tr -d '\n'
	make re -C libft/

%.o : %.c
	@echo "\033[33m[Doing object] \033[0m" | tr -d '\n'
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	@echo "\033[34m[Cleaning] \033[0m" | tr -d '\n'
	rm -f $(OBJ)

fclean: clean
	@echo "\033[34m[Filecleaning] \033[0m" | tr -d '\n'
	rm -f $(NAME)

ffclean: fclean
	make fclean -C libft/

re: fclean all

rre: remake re

run: all
	@echo "\033[32m[Running Binary]\033[0m" | tr -d '\n'
	@echo ""
	$(NAME) < anthills/kaka.map
