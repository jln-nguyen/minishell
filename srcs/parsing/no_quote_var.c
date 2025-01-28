/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:36 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/28 14:20:52 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	check_no_quote(t_token **head, t_token **tok, t_data *data, int *i)
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
