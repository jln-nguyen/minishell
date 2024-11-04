/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:11:39 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/30 19:25:46 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

typedef enum e_enum_type
{
	TOKEN_STR,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
}	t_enum_type;

typedef struct s_token
{
	t_enum_type		type;
	char			*value;
	struct s_token	*next;	
}	t_token;

int		check_syntax(char *str);
int		move_index(t_token *tok);

t_token	*new_tok(t_enum_type type, char *str);

t_token	*ft_token(char *str);

void	ft_tokadd_back(t_token **lst, t_token *new);
void	ft_free(t_token **tok);
void	ft_tokadd_back(t_token **lst, t_token *new);
t_token	*ft_del_last(t_token *tok);

void	print_token(t_token *tok); //a supp

#endif 