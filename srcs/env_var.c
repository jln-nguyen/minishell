/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:03:07 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/06 15:56:41 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*change_value(char *tok)
{
	char	*tmp;

	tmp = NULL;
	tmp = getenv(tok);
	if (!tmp)
		return (free(tok), NULL);
	free(tok);
	tok = ft_strdup(tmp);
	// free(tmp);
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
	free(tmp);
	return (tok);
}

void	sup_node_if(t_token **begin_list)
{
	t_token	*cur;

	cur = *begin_list;
	if (begin_list == NULL || *begin_list == NULL)
		return ;
	if (cur->value == NULL)
	{
		*begin_list = cur->next;
		// free(cur->value);
		free(cur);
		sup_node_if(begin_list);
	}
	else
	{
		cur = *begin_list;
		sup_node_if(&cur->next);
	}
}

t_token	*expand_var(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tok != NULL)
	{
		if (tok->type == TOKEN_ENV_VAR)
		{
			tok->value = change_value(tok->value);
			tok->type = TOKEN_STR;
		}
		tok = tok->next;
	}
	tok = tmp;
	sup_node_if(&tok);
	return (tok);
}
