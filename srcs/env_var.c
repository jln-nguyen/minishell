/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:03:07 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/05 14:33:04 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	if (str[i] == '\0')
		i -= 1;
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		return (NULL);
	tok = new_tok(TOKEN_ENV_VAR, tmp);
	if (!tok)
		return (NULL);
	free(tmp);
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
