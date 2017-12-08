# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/08 18:11:02 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2017/12/08 18:11:02 by clcreuso    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

CFLAGS = -Werror -Wextra -Wall

NAME = ft_ls

D_SRC = src/

D_LIBFT = libft/

SRC1 = 	ft_ls.c main.c print_ls.c sort_ls.c stock_params1.c stock_params2.c \
		tools_ft_ls.c

all: create

create:
	@$(CC) $(SRC1) -L libft -lft -o $(NAME) 
	@echo "\033[0;32m✅️    Fillit executable created."

clean:
	@rm -f $(OBJ)
	@echo "\033[0;31m🗑️    Deleting object files." 

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m🗑️    Deleting fillit executable." 

re: fclean all
