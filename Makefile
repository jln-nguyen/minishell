# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 14:41:21 by bvictoir          #+#    #+#              #
#    Updated: 2024/11/04 15:00:33 by bvictoir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME	= minishell

SRC_PATH = srcs/
OBJ_PATH = obj/
LIBFT_PATH = libft/

SRC		= a_supp.c			\
		syntax_checker.c	\
		tok_utils.c			\
		token.c				\
		main.c
SRCS	= ${addprefix $(SRC_PATH), $(SRC)}

OBJ		= $(SRC:.c=.o)
OBJS	= ${addprefix $(OBJ_PATH), $(OBJ)}

CC		= cc
CFLAGS	= -Wall -Wextra -Werror 	
INCLUDES = -I incs/
LIB		= libft.a

RM		= rm -rfd

RED			:= "\033[0;31m\033[1m"
GREEN		:= "\033[0;32m\033[1m"
BLUE		:= "\033[0;34m\033[1m"
YELLOW		:= "\033[1;33m\033[1m"
PURPLE		:= "\033[0;35m\033[1m"
CYAN		:= "\033[0;36m\033[1m"
WHITE		:= "\033[0;37m\033[1m"
NO_STYLE	:= "\033[0m"


all:		$(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
			$(CC) $(CFLAGS) $(INCLUDES) -c  $< -o $@

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

$(NAME): $(OBJS)
		make -C $(LIBFT_PATH)
		mv $(LIBFT_PATH)$(LIB) .
		$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LIB)
		echo $(GREEN)$(NAME) compiled!$(NO_STYLE)

clean:	
		$(RM) $(OBJ_PATH)
		make clean -C $(LIBFT_PATH)
		echo $(YELLOW)object clean! $(NO_STYLE)

fclean: 	
		$(RM) $(OBJ_PATH) $(NAME) $(LIB)
		make fclean -C $(LIBFT_PATH)
		echo $(RED)$(NAME) deleted!$(NO_STYLE)

re: fclean all
		echo $(PURPLE)$(NAME) reloaded!$(NO_STYLE)

.PHONY:  all clean fclean re