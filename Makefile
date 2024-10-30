# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 16:10:13 by junguyen          #+#    #+#              #
#    Updated: 2024/10/30 16:18:52 by junguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

GREEN = \033[0;32m

BLUE = \033[0;34m

RED = \033[0;31m

YELLOW = \033[0;33m

BOLD = \033[1m

RESET = \033[0m

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC_PATH = srcs/

SRC =	main.c syntax_checker.c token.c tok_utils.c a_supp.c \

SRCS = $(addprefix $(SRC_PATH), $(SRC))

LIBFT = libft

OBJ = $(SRCS:.c=.o)

.c.o:
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
		@echo "$(BLUE)...Compiling LIBFT...$(RESET)"
		@make -sC $(LIBFT)
		@echo "$(GREEN)LIBFT created$(RESET)"
		@echo "$(BLUE)...Compiling minishell...$(RESET)"
		@$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a $(MLX_FLAGS) -o $(NAME)
		@echo "$(GREEN)$(BOLD)minishell created$(RESET)"
    
all: $(NAME)

clean:
		@rm -f $(OBJ)
		@make clean -sC $(LIBFT)
		@echo "$(YELLOW)objects cleaned$(RESET)"

fclean: clean
		@rm -f $(NAME) 
		@make fclean -sC $(LIBFT)
		@echo "$(RED)$(BOLD)all clean$(RESET)"
    
re: fclean all

.PHONY: all clean fclean re