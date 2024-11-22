/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:24:48 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/21 17:47:52 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*word(char *str)
{
	int		i;
	char	*tmp;
	t_token	*tok;

	i = 0;
	tmp = NULL;
	tok = NULL;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34)
				i++;
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39)
				i++;
		}
		if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) // || str[i] == 39 || str[i] == 34 ||
			break ;
		i++;
	}
	tmp = ft_substr(str, 0, i);
	tok = new_tok(TOKEN_STR, tmp);
	if (!tok)
		return (NULL);
	free(tmp);
	if (ft_strchr(tok->value, '$') != NULL)
		tok->type = TOKEN_ENV_VAR;
	return (tok);
}

static t_token	*check_redirect(char *str)
{
	int		i;
	t_token	*tok;	

	i = 0;
	tok = NULL;
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			tok = new_tok(TOKEN_REDIR_APPEND, ">>");
		else
			tok = new_tok(TOKEN_REDIR_OUT, ">");
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			tok = new_tok(TOKEN_REDIR_HEREDOC, "<<");
		else
			tok = new_tok(TOKEN_REDIR_IN, "<");
	}
	if (!tok)
		return (NULL);
	return (tok);
}

static t_token	*check_token(char *str, t_token *tok)
{
	int		i;
	t_token	*element;	

	i = 0;
	element = NULL;
	if (str[i] == '|')
		element = new_tok(TOKEN_PIPE, "|");
	else if (str[i] == '<' || str[i] == '>')
		element = check_redirect(&str[i]);
	// else if (str[i] == 39 || str[i] == 34)
	// 	element = check_quote(&str[i + 1], str[i]);
	else
		element = word(&str[i]);
	if (!element)
		return (NULL);
	ft_tokadd_back(&tok, element);
	return (tok);
}

static void	expand_lst(t_token **tok, char *str)
{
	int		i;

	i = 0;
	if (!str[i])
		return ;
	while (str[i])
	{
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		else
		{
			*tok = check_token(&str[i], *tok);
			if (!tok)
				return ;
			i += move_index(*tok, str, i);
			// if (move_index(*tok, str, i) == 0)
			// 	*tok = ft_del_last(*tok);
		}
	}
}

t_token	*ft_token(char *str)
{
	int		i;
	t_token	*tok;

	i = 0;
	tok = NULL;
	if (!str)
		return (NULL);
	while (str[i] && tok == NULL)
	{
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		else
		{
			tok = check_token(&str[i], tok);
			if (!tok)
				return (NULL);
			i += move_index(tok, str, i);
			// if (move_index(tok, str, i) == 0)
			// 	tok = ft_del_last(tok);
		}
	}
	expand_lst(&tok, &str[i]);
	// tok = expand_var(tok);
	tok = expand_str(tok);
	return (tok);
}
