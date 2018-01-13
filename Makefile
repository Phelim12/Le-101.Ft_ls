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

DIR_INC = Includes/

DIR_SRC = Sources/

DIR_LIB = Libft/

NAME_SRC = 	main.c check_ls.c print_ls.c sort_ls.c stock_ls.c tools_ls.c

SRC =	$(addprefix $(DIR_SRC), $(NAME_SRC))

OBJ =	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(DIR_LIB)
	@$(CC) $(OBJ) -L $(DIR_LIB) -lft -o $(NAME) 
	@echo "\033[0;32m✅️    Fillit executable created."

./%.o: ./%.c
	@$(CC) $(CFLAGS) -I $(DIR_INC) -o $@ -c $< 
	@echo "\033[0;32m✅️    $@ created."

clean:
	@rm -f $(OBJ)
	@echo "\033[0;31m🗑️    Deleting object files." 

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m🗑️    Deleting fillit executable." 

re: fclean all

