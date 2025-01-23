/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:03:07 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/23 18:37:15 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_malloc_tok(t_token **tok, t_data *data)
{
	ft_free(tok);
	ft_free_env(&data->env);
	ft_printf(STDERR_FILENO, "Minishell: Malloc error\n");
	exit(EXIT_FAILURE);
}

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

// static int	move_index_quote(char *str, int i, char c)
// {
// 	int		j;

// 	j = 0;
// 	while (str[i + j] && str[i + j] != c)
// 		j++;
// 	if (j == 0 && i == 1 && str[i + j + 1] == '\0')
// 		return (2);
// 	return (j);
// }

static int	search_end_var(char *new_str, int i)
{
	int	j;

	j = 0;
	if (new_str[i] == '?')
		j = 1;
	else
	{
		while (new_str[i + j] && new_str[i + j] != '$'
			&& new_str[i + j] != 39 && new_str[i + j] != 34)
			j++;
	}
	return (j);
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

static char	*expand_var_env(char *new_str, int *i, t_data *data, t_token **head)
{
	int		j;
	char	**tmp;

	tmp = NULL;
	if (new_str[*i] == '\0')
		return (new_str);
	tmp = init_tmp();
	if (!tmp)
		return (free(new_str), NULL);
	j = search_end_var(new_str, *i);
	tmp[0] = ft_substr(new_str, *i, j);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	tmp[0] = change_value(tmp[0], data, head, tmp);
	tmp[1] = ft_substr(new_str, 0, *i - 1);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	tmp[2] = ft_substr(new_str, *i + j, ft_strlen(new_str) - *i - j);
	if (!tmp[2])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	free(new_str);
	*i += ft_strlen(tmp[0]) - 1;
	new_str = ft_strbigjoin(tmp[1], tmp[0], tmp[2]);
	ft_free_tab_var_env(&tmp);
	return (new_str);
}

static void	check_no_quote(t_token **head, t_token **tok, t_data *data, int *i)
{
	int	n;

	n = *i;
	if ((*tok)->value[n + 1] == '\0')
		return ;
	n++;
	(*tok)->value = expand_var_env((*tok)->value, &n, data, head);
	if (!(*tok)->value)
		error_malloc_tok(head, data);
	*i = n;
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
				(*tok)->value = handle_double_quote((*tok)->value, &i, data, head);
				if (!(*tok)->value)
					error_malloc_tok(head, data);
				(*tok)->value = remove_quote((*tok)->value, &i - 1, j, (*tok)->value[j]);
				printf("i = %d\n", i);
				// i--;
			}
			else
				(*tok)->value = remove_quote((*tok)->value, &i, j, (*tok)->value[j]);
			// i += move_index_quote((*tok)->value, i + 1, (*tok)->value[j]);
			// printf("j = %d\n", j);
			// (*tok)->value = remove_quote((*tok)->value, j, i, (*tok)->value[j]);
			if (!(*tok)->value)
				error_malloc_tok(head, data);
		}
		else if ((*tok)->value[i] == '$' && bool != 1)
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
