/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:35:03 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/09 18:17:24 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strtrim_whitespace(const char *s1)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1)
		return (NULL);
	start = 0;
	if (s1[start] == '"')
		start++;
	while (s1[start] && ft_is_space(s1[start]) == 0)
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_is_space(s1[end - 1]) == 0)
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}

void	check_whitespace(char **tmp)
{
	char	*str;

	str = ft_strtrim_whitespace(tmp[0]);
	if (!str)
		return ; //protect malloc
	free(tmp[0]);
	if (ft_strlen(tmp[1]) > 0 && ft_strlen(tmp[2]) > 0)
		tmp[0] = ft_strbigjoin(" ", str, " ");
	else if (ft_strlen(tmp[1]) > 0
		&& ft_is_space(tmp[1][ft_strlen(tmp[1]) - 1]) == 1)
		tmp[0] = ft_strjoin(" ", str);
	else if (ft_strlen(tmp[2]) > 0 && ft_is_space(tmp[2][0]) == '$')
		tmp[0] = ft_strjoin(str, " ");
	else
		tmp[0] = ft_strdup(str);
	if (!tmp[0])
		return ; //protect malloc
	free(str);
}

char	*ft_pre_bigjoin_trim(char *new_str, char **tmp, int i, int j)
{
	int	n;

	n = 0;
	tmp[2] = ft_substr(new_str, i + j, ft_strlen(new_str) - i - j);
	if (!tmp[2])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	free(new_str);
	if (tmp[0])
	{
		while (tmp[0][n])
		{
			if (ft_is_space(tmp[0][n]) == 0)
			{
				check_whitespace(tmp);
				break ;
			}
			n++;
		}
	}
	new_str = ft_strbigjoin(tmp[1], tmp[0], tmp[2]);
	return (new_str);
}
