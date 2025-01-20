/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:03:07 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/16 15:03:26 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sup_node_if(t_token **begin_list)
{
	t_token	*cur;

	cur = *begin_list;
	if (begin_list == NULL || *begin_list == NULL)
		return ;
	// if (cur->value[0] == 34 || cur->value[0] == 39)
	// 	cur->value = handle_quote(cur->value, 1, 0);
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

static int	move_index_quote(char *str, int i, char c)
{
	int		j;

	j = 0;
	while (str[i + j] && str[i + j] != c)
		j++;
	return (j);
}

static char	*expand_var_env(char *new_str, int i, t_data *data, int bool)
{
	int		j;
	char	**tmp;

	tmp = NULL;
	if (new_str[i] == '\0')
		return (new_str);
	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		return (free(new_str), NULL);
	tmp[3] = 0;
	j = 0;
	if (new_str[i] == '?')
		j = 1;
	else
	{
		while (new_str[i + j] && new_str[i + j] != '$' && new_str[i + j] != 39
			&& new_str[i + j] != 34)
			j++;
	}
	tmp[0] = ft_substr(new_str, i, j);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	tmp[0] = change_value(tmp[0], data);
	tmp[1] = ft_substr(new_str, 0, i - 1);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	tmp[2] = ft_substr(new_str, i + j, ft_strlen(new_str) - i - j);
	if (!tmp[2])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	free(new_str);
	// new_str = ft_pre_bigjoin_trim(new_str, tmp, i, j);
	// if (!new_str)
	// 	return (ft_free_tab_var_env(&tmp), NULL);
	if (bool == 0)
	{
		tmp[0] = ft_pre_bigjoin_trim(tmp);
		if (!tmp[0])
			return (ft_free_tab_var_env(&tmp), NULL);
	}
	new_str = ft_strbigjoin(tmp[1], tmp[0], tmp[2]);
	return (ft_free_tab_var_env(&tmp), new_str);
}

static void	change_value_env_var(t_token **tok, t_data *data, int bool)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while ((*tok)->value[i])
	{
		if ((*tok)->value[i] == 39 || (*tok)->value[i] == 34)
		{
			j = (*tok)->value[i];
			i++;
			while ((*tok)->value[i] && (*tok)->value[i] != j)
				i++;
		}
		if ((*tok)->value[i] == '$' && bool != 1)
		{
			if ((*tok)->value[i + 1] == '\0')
				break ;
			(*tok)->value = expand_var_env((*tok)->value, i + 1, data, bool);
		}
		else
			i++;
	}
	i = 0;
	if ((*tok)->value[i] == '\0')
		return ;
	if (ft_is_space((*tok)->value[ft_strlen((*tok)->value) - 1]) == 0)
	{
		tmp = ft_substr((*tok)->value, 0, i -1);
		if (!tmp)
			return ;
		free((*tok)->value);
		(*tok)->value = ft_strdup(tmp);
		if (!(*tok)->value)
			return ;
		free(tmp);
	}

}

static void	quotes_process(t_token **tok, t_data *data, int bool)
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
				(*tok)->value = handle_double_quote((*tok)->value, j, data);
			i += move_index_quote((*tok)->value, i + 1, (*tok)->value[j]);
			(*tok)->value = remove_quote((*tok)->value, j, (*tok)->value[j]);
		}
		else
			i++;
	}
}

t_token	*expand_str(t_token *tok, t_data *data)
{
	t_token	*tmp;
	int		bool;

	tmp = tok;
	bool = 0;
	while (tok)
	{
		if (tok->type == TOKEN_REDIR_HEREDOC && (tok->next->type == TOKEN_STR
				|| tok->next->type == TOKEN_ENV_VAR))
			bool = 1;
		else if (tok->type != TOKEN_STR && tok->type != TOKEN_ENV_VAR && tok->type != TOKEN_PIPE
			&& (tok->next->type == TOKEN_STR || tok->next->type == TOKEN_ENV_VAR))
			bool = 2;
		else if (tok->type == TOKEN_STR || tok->type == TOKEN_ENV_VAR)
		{
			change_value_env_var(&tok, data, bool);
			if (!tok->value)
				return (ft_free(&tok), NULL);
			tok->type = TOKEN_STR;
			bool = 0;
		}
		tok = tok->next;
	}
	tok = tmp;
	sup_node_if(&tok);
	if (!tok)
		return (NULL);
	while (tok)
	{
		if (tok->type == TOKEN_REDIR_HEREDOC && (tok->next->type == TOKEN_STR
				|| tok->next->type == TOKEN_ENV_VAR))
			bool = 1;
		if (tok->type == TOKEN_STR || tok->type == TOKEN_ENV_VAR)
		{
			quotes_process(&tok, data, bool);
			if (!tok->value)
				return (ft_free(&tok), NULL);
			tok->type = TOKEN_STR;
		}
		tok = tok->next;
	}
	tok = tmp;
	return (tok);
}
