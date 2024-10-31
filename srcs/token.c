/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:24:48 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/31 20:57:23 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*change_value(char *tok)
{
	char	*tmp;

	tmp = NULL;
	tmp = getenv(tok);
	if (!tmp)
		return (NULL);
	free(tok);
	tok = ft_strdup(tmp);
	if (!tok)
		return (NULL);
	return (tok);
}

t_token	*expand_var(t_token *tok)
{
	while (tok != NULL)
	{
		if (tok->type == TOKEN_ENV_VAR)
			tok->value = change_value(tok->value);
		tok = tok->next;
	}
	return (tok);
}

char	*handle_double_quote(char *str)
{
	int		i;
	int		end;
	char	*new_str;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	new_str = NULL;
	tmp1 = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	while(str[i] && str[i] != 34)
		i++;
	new_str = ft_substr(str, 0, i);
	if (!new_str)
		return (NULL);
	i = 0;
	while (new_str[i])
	{
		if (new_str[i] == '$')
		{
			end = 0;
			i++;
			while (new_str[i + end] != 34 && new_str[i + end] != 32 && str[i + end])
				end++;
			tmp1 = ft_substr(new_str, i, end);
			tmp1 = change_value(tmp1);
			if (!tmp1)
				return (NULL);
			tmp2 = ft_substr(new_str, 0, i - 1);
			if (!tmp2)
				return (NULL);
			tmp3 = ft_strjoin(tmp2, tmp1);
			if (!new_str)
				return (NULL);
			free(tmp2);
			tmp2 = ft_substr(new_str, i + end, ft_strlen(new_str));
			if (!tmp2)
				return (NULL);
			free(tmp1);
			tmp1 = ft_strjoin(tmp3, tmp2);
			if (!tmp1)
				return (NULL);
			free(tmp2);
			free(tmp3);
			free(new_str);
			new_str = ft_strdup(tmp1);
			if (!new_str)
				return (NULL);
			free(tmp1);
			i += end;
		}
		i++;
	}
	return (new_str);
}

t_token	*check_quote(char *str, char c)
{
	int		i;
	char	*tmp;
	t_token	*tok;

	i = 0;
	tmp = NULL;
	tok = NULL;
	if (c == 34)
	{
		tmp = handle_double_quote(str);
		if (tmp)
		{
			tok = new_tok(TOKEN_STR, tmp);
			if (!tok)
				return (NULL);
			free(tmp);
			return (tok);
		}
	}
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
	while (str[i] && str[i] != 32)
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>'
			|| str[i] == 39 || str[i] == 34 || str[i] == '$' || (str[i] >= 9 && str[i] <= 13))
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

t_token	*check_env_var(char *str)
{
	int		i;
	t_token	*tok;	
	char	*tmp;

	i = 0;
	tok = NULL;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>'
			|| str[i] == 39 || str[i] == 34 || str[i] == 32)
			break ;
		i++;
	}
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		return (NULL);
	tok = new_tok(TOKEN_ENV_VAR, tmp);
	if (!tok)
		return (NULL);
	free(tmp);
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

int	move_to_end_quote(char *str, char c)
{
	int	i;

	i = 0;
	i++;
	while (str[i] != c)
		i++;
	i++;
	return (i);
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
			*tok = check_token(&str[i], *tok); //a proteger
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
