/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:24:48 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/30 19:35:31 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_token	*check_quote(char *str, char c)
{
	int		i;
	char	*tmp;
	t_token	*tok;

	i = 0;
	tmp = NULL;
	tok = NULL;
	while (str[i] != c)
		i++;
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		return (NULL);
	tok = new_tok(TOKEN_STR, tmp);
	if (!tok)
		return (NULL);
	free(tmp);
	return (tok);
}

t_token	*word(char *str)
{
	int		i;
	char	*tmp;
	t_token	*tok;

	i = 0;
	tmp = NULL;
	tok = NULL;
	while (str[i] || (str[i] != 32 && (str[i] >= 9 && str[i] <= 13)))
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == 39 || str[i] == '"')
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
	else if (str[i] == 39)
		element = check_quote(&str[i + 1], 39);
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
	while (str[i])
	{
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		else
		{
			*tok = check_token(&str[i], *tok); //a proteger
			if (str[i] == 39)
				i += 2;
			i += move_index(*tok);
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
	while (str[i])
	{
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		else
		{
			tok = check_token(&str[i], tok);
			if (!tok)
				return (NULL);
			if (str[i] == 39)
				i += 2;
			i += ft_strlen(tok->value);
			if (ft_strlen(tok->value) == 0)
				tok = ft_del_last(tok);
			else
				break ;
		}
	}
	expand_lst(&tok, &str[i]);
	print_token(tok);
	return (tok);
}
