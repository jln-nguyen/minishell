/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:01:11 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/28 14:34:45 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
