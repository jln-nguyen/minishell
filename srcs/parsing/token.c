/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:24:48 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/21 15:34:28 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*word(char *str, int i)
{
	char	c;
	char	*tmp;
	t_token	*tok;

	while (str[i] && str[i] != '|' && str[i] != '<' && str[i] != '>'
		&& str[i] != 32 && !(str[i] >= 9 && str[i] <= 13))
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i];
			i++;
			while (str[i] != c)
				i++;
		}
		i++;
	}
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		return (NULL);
	tok = new_tok(TOKEN_STR, tmp);
	if (!tok)
		return (free(tmp), NULL);
	if (ft_strchr(tok->value, '$') != NULL)
		tok->type = TOKEN_ENV_VAR;
	return (free(tmp), tok);
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

t_token	*check_token(char *str, t_token *tok)
{
	int		i;
	t_token	*element;	

	i = 0;
	element = NULL;
	if (str[i] == '|')
		element = new_tok(TOKEN_PIPE, "|");
	else if (str[i] == '<' || str[i] == '>')
		element = check_redirect(&str[i]);
	else
		element = word(&str[i], i);
	if (!element)
		return (NULL);
	ft_tokadd_back(&tok, element);
	return (tok);
}

int	expand_lst(t_token **tok, char *str)
{
	int		i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		else
		{
			*tok = check_token(&str[i], *tok);
			if (!tok)
				return (-1);
			i += move_index(*tok);
		}
	}
	return (0);
}
