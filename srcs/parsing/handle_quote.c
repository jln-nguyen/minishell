/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:01:11 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/09 18:26:41 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_str(char *str, int i, t_env *env)
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
	j = 0;
	if (str[i] == '?')
		j = 1;
	else
	{
		while (ft_is_space(str[i + j]) && str[i + j] && str[i + j] != '$'
			&& str[i + j] != 39 && str[i + j] != 34)
			j++;
	}
	tmp[0] = ft_substr(str, i, j);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), free(str), NULL);
	tmp[0] = change_value(tmp[0], env);
	tmp[1] = ft_substr(str, 0, i - 1);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), free(str), NULL);
	str = ft_pre_bigjoin(str, tmp, i, j);
	if (!str)
		return (ft_free_tab_var_env(&tmp), NULL);
	return (ft_free_tab_var_env(&tmp), str);
}

static char	*check_expand_var(char *str, int i, int j, t_env *env)
{
	char	*new_str;

	new_str = NULL;
	new_str = ft_substr(str, i, j);
	if (!new_str)
		return (NULL);
	i = 0;
	while (new_str[i])
	{
		if (new_str[i] == '$')
		{
			new_str = change_str(new_str, i + 1, env);
			if (!new_str)
				return (NULL);
			if (new_str[i] == '\0')
				break ;
		}
		i++;
	}
	return (new_str);
}

char	*handle_double_quote(char *str, int i, t_env *env)
{
	int		j;
	char	**tmp;
	char	*new_str;

	j = 0;
	new_str = NULL;
	while (str[i + j + 1] && str[i + j + 1] != 34)
		j++;
	j += 2;
	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		return (free(new_str), NULL);
	tmp[3] = 0;
	tmp[1] = ft_substr(str, 0, i);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[0] = check_expand_var(str, i, j, env);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), NULL);
	new_str = ft_pre_bigjoin(str, tmp, i, j);
	if (!new_str)
		return (ft_free_tab_var_env(&tmp), NULL);
	return (ft_free_tab_var_env(&tmp), new_str);
}

char	*handle_quote(char *str, int i, int j)
{
	char	**tmp;
	char	*new_str;

	new_str = NULL;
	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		return (free(new_str), NULL);
	tmp[3] = 0;
	tmp[0] = ft_substr(str, 0, i - 1);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[1] = ft_substr(str, i, j);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[2] = ft_substr(str, i + j + 1, ft_strlen(str) - i - j - 1);
	if (!tmp[2])
		return (ft_free_tab_var_env(&tmp), NULL);
	new_str = ft_strbigjoin(tmp[0], tmp[1], tmp[2]);
	if (!new_str)
		return (ft_free_tab_var_env(&tmp), NULL);
	return (ft_free_tab_var_env(&tmp), new_str);
}

char	*remove_quote(char *str, int i, char c)
{
	int		j;
	char	*new_str;

	j = 0;
	new_str = NULL;
	i++;
	while (str[i + j] && str[i + j] != c)
		j++;
	new_str = handle_quote(str, i, j);
	free(str);
	if (!new_str)
		return (NULL);
	return (new_str);
}
