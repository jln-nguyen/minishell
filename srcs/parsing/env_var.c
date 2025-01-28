/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:03:07 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/28 15:06:06 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sup_node_if(t_token **begin_list)
{
	t_token	*cur;

	cur = *begin_list;
	if (begin_list == NULL || *begin_list == NULL)
		return ;
	if (cur->value == NULL || cur->value[0] == '\0')
	{
		*begin_list = cur->next;
		if (cur->value)
			free(cur->value);
		free(cur);
		sup_node_if(begin_list);
	}
	else
	{
		cur = *begin_list;
		sup_node_if(&cur->next);
	}
}

char	**init_tmp(void)
{
	char	**tmp;

	tmp = NULL;
	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		return (NULL);
	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = 0;
	tmp[3] = 0;
	return (tmp);
}

static void	check_str(t_token **head, t_token **tok, t_data *data, int bool)
{
	int	i;
	int	j;

	i = 0;
	while ((*tok)->value[i])
	{
		if ((*tok)->value[i] == 39 || (*tok)->value[i] == 34)
		{
			j = i;
			if ((*tok)->value[j] == 34 && bool != 1)
			{
				(*tok)->value = dble_quote((*tok)->value, &i, data, head);
				(*tok)->value = rem_double_quote((*tok)->value, &i, j + 1);
			}
			else
				(*tok)->value = rem_quote((*tok)->value, &i, (*tok)->value[j]);
			if (!(*tok)->value)
				error_malloc_tok(head, data);
		}
		else if ((*tok)->value[i] == '$' && bool != 1 && (*tok)->value[i + 1])
			check_no_quote(head, tok, data, &i);
		else
			i++;
	}
}

static void	remove_empty_quotes(t_token **tok, t_data *data)
{
	t_token	*tmp;

	tmp = *tok;
	while (tmp)
	{
		if ((tmp->value[0] == 34 && tmp->value[1] == 34)
			|| (tmp->value[0] == 39 && tmp->value[1] == 39))
		{
			free(tmp->value);
			tmp->value = ft_strdup("");
			if (!tmp->value)
				error_malloc_tok(tok, data);
		}
		tmp = tmp->next;
	}
}

t_token	*expand_str(t_token *tok, t_data *data)
{
	t_token	*tmp;
	int		bool;

	tmp = tok;
	bool = 0;
	if (!tok)
		return (NULL);
	while (tok)
	{
		if (tok->type == TOKEN_REDIR_HEREDOC && (tok->next->type == TOKEN_STR
				|| tok->next->type == TOKEN_ENV_VAR))
			bool = 1;
		if (tok->type == TOKEN_STR || tok->type == TOKEN_ENV_VAR)
		{
			check_str(&tmp, &tok, data, bool);
			tok->type = TOKEN_STR;
		}
		tok = tok->next;
	}
	tok = tmp;
	sup_node_if(&tok);
	remove_empty_quotes(&tok, data);
	return (tok);
}
