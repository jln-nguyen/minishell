/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:24:48 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/04 15:28:57 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_token	*word(char *str)
{
	int		i;
	char	*tmp;
	t_token	*tok;

	i = 0;
	tmp = NULL;
	tok = NULL;
	while (str[i] && str[i] != 32)
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == 39
			|| str[i] == 34 || str[i] == '$' || (str[i] >= 9 && str[i] <= 13))
			break ;
		i++;
	}
	tmp = ft_substr(str, 0, i);
	tok = new_tok(TOKEN_STR, tmp);
	if (!tok)
		return (NULL);
	free(tmp);
	return (tok);
}

t_token	*check_redirect(char *str)
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
	char	*tmp;	

	i = 0;
	tmp = NULL;
	element = NULL;
	if (str[i] == '|')
		element = new_tok(TOKEN_PIPE, "|");
	else if (str[i] == '<' || str[i] == '>')
		element = check_redirect(&str[i]);
	else if (str[i] == 39 || str[i] == 34)
		element = check_quote(&str[i + 1], str[i]);
	else if (str[i] == '$')
		element = check_env_var(&str[i + 1]);
	else
		element = word(&str[i]);
	if (!element)
		return (NULL);
	ft_tokadd_back(&tok, element);
	return (tok);
}

void	expand_lst(t_token **tok, char *str)
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
			if (str[i] == 39 || str[i] == 34)
				i += move_to_end_quote(&str[i], str[i]);
			else
			{
				if (str[i] == '$')
					i++;
				i += move_index(*tok);
			}
			if (move_index(*tok) == 0)
				*tok = ft_del_last(*tok);
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
			if (str[i] == 39 || str[i] == 34)
				i += move_to_end_quote(&str[i], str[i]);
			else
			{
				if (str[i] == '$')
					i++;
				i += move_index(tok);
			}
			if (move_index(tok) == 0)
				tok = ft_del_last(tok);
		}
	}
	expand_lst(&tok, &str[i]);
	expand_var(tok);
	return (tok);
}
