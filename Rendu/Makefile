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

NAME = ft_ls

C_FLAGS = -Wall -Wextra -Werror

DIR_INC = Includes/

DIR_SRC = Sources/

DIR_LIB = Libft/

NAME_SRC = 	main_ls.c find_law_ls.c	tools_a_ls.c tools_b_ls.c find_files_ls.c \
			sort_files_ls.c print_files_ls.c find_params_ls.c print_error_ls.c \
			find_option_ls.c multi_bonus_ls.c column_bonus_ls.c

SRC =	$(addprefix $(DIR_SRC), $(NAME_SRC))

OBJ =	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(DIR_LIB)
	@$(CC) $(C_FLAGS) $(OBJ) -L $(DIR_LIB) -lft -o $(NAME) 
	@echo "\033[0;32m✅️   make ft_ls."

./%.o: ./%.c
	@$(CC) $(C_FLAGS) -I $(DIR_INC) -o $@ -c $< 
	@echo "\033[0;32m✅️   $@ created."

clean:
	@make clean -C $(DIR_LIB)
	@rm -f $(OBJ)
	@echo "\033[38;5;202m🗑️   clean ft_ls.\033[0m\033[K" 

fclean: clean
	@make fclean -C $(DIR_LIB)
	@rm -f $(NAME)
	@echo "\033[38;5;196m🗑️   fclean ft_ls.\033[0m\033[K" 

re: fclean all

