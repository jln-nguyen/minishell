/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:01:11 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/13 11:02:37 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (str[i] && str[i] != 34)
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
			while (new_str[i + end] != 32 && new_str[i + end] && new_str[i + end] != '$')
				end++;
			tmp1 = ft_substr(new_str, i, end); //protect malloc
			tmp1 = change_value(tmp1);
			tmp2 = ft_substr(new_str, 0, i - 1);
			if (!tmp2)
				return (NULL);
			tmp3 = ft_strjoin(tmp2, tmp1);
			if (!tmp3)
				return (NULL);
			free(tmp2);
			tmp2 = ft_substr(new_str, i + end, ft_strlen(new_str));
			if (!tmp2)
				return (NULL);
			if (tmp1)
				free(tmp1);
			tmp1 = ft_strjoin(tmp3, tmp2);
			if (!tmp1)
				return (NULL);
			free(tmp2);
			i = ft_strlen(tmp3);
			free(tmp3);
			free(new_str);
			new_str = ft_strdup(tmp1);
			if (!new_str)
				return (free(tmp1), NULL);
			free(tmp1);
		}
		else
			i++;
	}
	return (new_str);
}

t_token	*handle_quote(char *str)
{
	int		i;
	char	*tmp;
	t_token	*tok;

	i = 0;
	tmp = NULL;
	while (str[i] != 39)
		i++;
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		return (NULL);
	tok = new_tok(TOKEN_STR, tmp);
	free(tmp);
	return (tok);
}

t_token	*check_quote(char *str, char c)
{
	char	*tmp;
	t_token	*tok;

	tmp = NULL;
	tok = NULL;
	if (c == 34)
	{
		tmp = handle_double_quote(str);
		if (!tmp)
			return (NULL);
		tok = new_tok(TOKEN_STR, tmp);
		free(tmp);
	}
	else
		tok = handle_quote(str);
	return (tok);
}
