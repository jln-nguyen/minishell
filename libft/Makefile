# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 14:41:17 by bvictoir          #+#    #+#              #
#    Updated: 2024/11/04 14:41:18 by bvictoir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	+= -s

NAME		= libft.a

SRC_PATH	= srcs/
OBJ_PATH	= obj/

SRC			= ft_isalpha.c				\
				ft_isalnum.c			\
				ft_isprint.c			\
				ft_isdigit.c			\
				ft_isascii.c			\
				ft_strlen.c				\
				ft_memset.c				\
				ft_bzero.c				\
				ft_memcpy.c				\
				ft_memmove.c			\
				ft_strlcpy.c			\
				ft_strlcat.c			\
				ft_toupper.c			\
				ft_tolower.c			\
				ft_strchr.c				\
				ft_strrchr.c			\
				ft_strncmp.c			\
				ft_memchr.c				\
				ft_memcmp.c				\
				ft_strnstr.c			\
				ft_atoi.c				\
				ft_calloc.c				\
				ft_strdup.c				\
				ft_substr.c				\
				ft_strjoin.c			\
				ft_strtrim.c			\
				ft_split.c				\
				ft_itoa.c				\
				ft_strmapi.c			\
				ft_striteri.c			\
				ft_putchar_fd.c			\
				ft_putstr_fd.c			\
				ft_putendl_fd.c			\
				ft_putnbr_fd.c			\
				ft_lstnew_bonus.c		\
				ft_lstadd_front_bonus.c	\
				ft_lstsize_bonus.c		\
				ft_lstlast_bonus.c		\
				ft_lstadd_back_bonus.c	\
				ft_lstdelone_bonus.c	\
				ft_lstclear_bonus.c		\
				ft_lstiter_bonus.c		\
				ft_lstmap_bonus.c		\
				get_next_line.c			\
				get_next_line_utils.c	\
				ft_printf.c				\
				ft_diu.c				\
				ft_ifcspc.c				\
				ft_ifpxX.c				\
				ft_printf_utils.c		\
				ft_free_tab.c
SRCS		= ${addprefix $(SRC_PATH), $(SRC)}

OBJ			= $(SRC:.c=.o)
OBJS		= ${addprefix $(OBJ_PATH), $(OBJ)}

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
INCS		= -I ../incs/

AR			= ar rc
RM			= rm -rfd

RED			:= "\033[0;31m\033[1m"
GREEN		:= "\033[0;32m\033[1m"
BLUE		:= "\033[0;34m\033[1m"
YELLOW		:= "\033[1;33m\033[1m"
PURPLE		:= "\033[0;35m\033[1m"
CYAN		:= "\033[0;36m\033[1m"
WHITE		:= "\033[0;37m\033[1m"
NO_STYLE	:= "\033[0m"


all: $(OBJ_PATH) $(NAME)


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJ_PATH):
		mkdir -p $(OBJ_PATH)

$(NAME): $(OBJS)
		$(AR) $(NAME) $(OBJS)
		echo $(GREEN)$(NAME) compiled!$(NO_STYLE)

clean:
		$(RM) $(OBJ_PATH)
		echo $(YELLOW)object clean! $(NO_STYLE)

fclean: clean
		$(RM) $(NAME)
		echo $(RED)$(NAME) deleted!$(NO_STYLE)

re: fclean all
		echo $(PURPLE)$(NAME) reloaded!$(NO_STYLE)

.PHONY: all clean fclean re
