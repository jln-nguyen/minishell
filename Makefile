# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 14:41:21 by bvictoir          #+#    #+#              #
#    Updated: 2025/01/29 13:40:30 by bvictoir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME	= minishell

SRC_PATH = srcs/
OBJ_PATH = obj/
LIBFT_PATH = libft/

SRC		= main.c					\
		parsing/ft_free.c			\
		parsing/no_quote_var.c		\
		parsing/handle_dble_quote.c	\
		parsing/syntax_checker.c	\
		parsing/tok_utils.c			\
		parsing/token.c				\
		parsing/env_var.c			\
		parsing/handle_quote.c		\
		parsing/ast.c				\
		parsing/ast_str.c			\
		parsing/ast_op.c			\
		parsing/set_env.c			\
		parsing/parsing.c			\
		parsing/env_var_utils.c		\
		parsing/create_env.c		\
		builtins/ft_echo.c			\
		builtins/ft_env.c			\
		builtins/ft_exit.c			\
		builtins/ft_exit_utils.c	\
		builtins/ft_export.c		\
		builtins/ft_unset.c			\
		builtins/ft_print_export.c	\
		builtins/ft_pwd.c			\
		builtins/ft_cd.c			\
		exec/ft_exec.c				\
		exec/ft_exec_utils.c		\
		exec/ft_execve.c			\
		exec/ft_execve_utils.c		\
		exec/ft_check_redir.c		\
		exec/ft_redir_fd.c			\
		exec/save_cmd.c				\
		exec/ft_heredoc.c			\
		exec/ft_pipe.c
SRCS	= ${addprefix $(SRC_PATH), $(SRC)}

OBJ		= $(SRC:.c=.o)
OBJS	= ${addprefix $(OBJ_PATH), $(OBJ)}

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g 
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


all:		$(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
			mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDES) -c  $< -o $@

$(NAME): $(OBJS)
		make -C $(LIBFT_PATH)
		mv $(LIBFT_PATH)$(LIB) .
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LIB) -lreadline
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
