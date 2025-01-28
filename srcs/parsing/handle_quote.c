/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:01:11 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/28 13:18:12 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index(char *str, int i)
{
	int	j;

	j = 0;
	if (str[i] == '?')
		j = 1;
	else
	{
		while (ft_is_space(str[i + j]) && str[i + j] && str[i + j] != '$'
			&& str[i + j] != 39 && str[i + j] != 34)
			j++;
	}
	return (j);
}

char	*change_str(char *str, int i, t_data *data, t_token **head)
{
	int		j;
	char	**tmp;

	tmp = NULL;
	if (str[i] == '\0' || str[i] == 34 || str[i] == 39 || !ft_is_space(str[i]))
		return (str);
	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		return (free(str), NULL);
	tmp[3] = 0;
	j = get_index(str, i);
	tmp[0] = ft_substr(str, i, j);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), free(str), NULL);
	tmp[0] = change_value(tmp[0], data, head, tmp);
	tmp[1] = ft_substr(str, 0, i - 1);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), free(str), NULL);
	str = ft_pre_bigjoin(str, tmp, i, j);
	if (!str)
		return (ft_free_tab_var_env(&tmp), NULL);
	return (ft_free_tab_var_env(&tmp), str);
}

static char	*check_expand_var(char *str, t_data *data, t_token **head)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '\0' || ft_is_space(str[i + 1]) == 0
				|| str[i + 1] == 39 || str[i + 1] == 34)
				i++;
			else
				str = change_str(str, i + 1, data, head);
			if (!str)
				return (NULL);
			if (str[i] == '\0')
				break ;
		}
		else
			i++;
	}
	return (str);
}

char	**split_str(char **tmp, char *str, int *i, int j)
{
	tmp[1] = ft_substr(str, 0, *i);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[0] = ft_substr(str, *i, j);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), NULL);
	return (tmp);
}

char	*dble_quote(char *str, int *i, t_data *data, t_token **head)
{
	int		j;
	char	**tmp;
	char	*new_str;

	j = 0;
	new_str = NULL;
	while (str[*i + j + 1] && str[*i + j + 1] != 34)
		j++;
	if (j == 0)
		return (*i += 1, str);
	j += 2;
	tmp = init_tmp();
	if (!tmp)
		return (free(str), NULL);
	tmp = split_str(tmp, str, i, j);
	if (!tmp)
		return (free(str), NULL);
	tmp[0] = check_expand_var(tmp[0], data, head);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), free(str), NULL);
	new_str = ft_pre_bigjoin(str, tmp, *i, j);
	if (!new_str)
		return (ft_free_tab_var_env(&tmp), free(str), NULL);
	*i += ft_strlen(tmp[0]) - 1;
	return (ft_free_tab_var_env(&tmp), new_str);
}

char	*rem_double_quote(char *str, int *i, int j)
{
	char	**tmp;
	char	*new_str;

	new_str = NULL;
	if (!str)
		return (NULL);
	if (j == 1 && *i == 1 && str[*i + 1] == '\0')
		return (*i += 1, str);
	tmp = init_tmp();
	if (!tmp)
		return (NULL);
	tmp[0] = ft_substr(str, 0, j - 1);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[1] = ft_substr(str, j, *i - j);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[2] = ft_substr(str, *i + 1, ft_strlen(str) - *i - 1);
	if (!tmp[2])
		return (ft_free_tab_var_env(&tmp), NULL);
	new_str = ft_strbigjoin(tmp[0], tmp[1], tmp[2]);
	if (!new_str)
		return (ft_free_tab_var_env(&tmp), NULL);
	*i = ft_strlen(tmp[0]) + ft_strlen(tmp[1]);
	return (ft_free_tab_var_env(&tmp), free(str), new_str);
}

char	*handle_quote(char *str, int **i, int j)
{
	char	**tmp;
	char	*new_str;

	new_str = NULL;
	tmp = init_tmp();
	if (!tmp)
		return (free(new_str), NULL);
	tmp[0] = ft_substr(str, 0, **i - 1);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[1] = ft_substr(str, **i, j);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[2] = ft_substr(str, **i + j + 1, ft_strlen(str) - **i - j - 1);
	if (!tmp[2])
		return (ft_free_tab_var_env(&tmp), NULL);
	new_str = ft_strbigjoin(tmp[0], tmp[1], tmp[2]);
	if (!new_str)
		return (ft_free_tab_var_env(&tmp), NULL);
	**i = ft_strlen(tmp[0]) + ft_strlen(tmp[1]);
	return (ft_free_tab_var_env(&tmp), new_str);
}

char	*rem_quote(char *str, int *i, char c)
{
	int		j;
	char	*new_str;

	j = 0;
	new_str = NULL;
	*i += 1 ;
	while (str[*i + j] && str[*i + j] != c)
		j++;
	if (j == 0 && *i == 1 && str[*i + j + 1] == '\0')
		return (str);
	new_str = handle_quote(str, &i, j);
	free(str);
	if (!new_str)
		return (NULL);
	return (new_str);
}
