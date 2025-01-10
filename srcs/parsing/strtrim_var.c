/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:35:03 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/10 17:49:15 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*skip_ws(const char *s1, int i)
{
	int		skip;
	char	*str;

	skip = 0;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i + skip])
	{
		if (ft_is_space(s1[i + skip]) == 0)
		{
			str[i] = s1[i + skip];
			i++;
		}
		while (s1[i + skip] && ft_is_space(s1[i + skip]) == 0)
			skip++;
		while (s1[i + skip] && ft_is_space(s1[i + skip]) != 0)
		{
			str[i] = s1[i + skip];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_strtrim_whitespace(const char *s1)
{
	int		skip;
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	skip = 0;
	i = 0;
	while (s1[i + skip])
	{
		if (ft_is_space(s1[i + skip]) == 0)
			i++;
		while (s1[i + skip] && ft_is_space(s1[i + skip]) == 0)
			skip++;
		while (s1[i + skip] && ft_is_space(s1[i + skip]) != 0)
			i++;
	}
	str = skip_ws(s1, i);
	if (!str)
		return (NULL); //protect
	return (str);
}

static char	*ft_remove_space(char *str, int n)
{
	char	*new_str;

	new_str = NULL;
	if (n == 0)
		new_str = ft_substr(str, 1, ft_strlen(str));
	else
		new_str = ft_substr(str, 0, ft_strlen(str) - 1);
	if (!new_str)
		return (NULL);
	free(str);
	return (new_str);
}

void	check_whitespace(char **tmp)
{
	char	*str;

	str = ft_strtrim_whitespace(tmp[0]);
	if (!str)
		return ; //protect malloc
	free(tmp[0]);
	if (ft_strlen(tmp[1]) == 0 || (ft_strlen(tmp[1]) > 0 && ft_is_space(tmp[1][ft_strlen(tmp[1]) - 1]) == 0))
	{
		if (ft_is_space(str[0]) == 0)
		{
			str = ft_remove_space(str, 0);
			if (!str)
				return ; //protect
		}
	}
	if (ft_strlen(tmp[2]) == 0 || (ft_strlen(tmp[2]) > 0 && ft_is_space(tmp[2][0]) == 0))
	{
		if (ft_is_space(str[ft_strlen(str) - 1]) == 0)
		{
			str = ft_remove_space(str, 1);
			if (!str)
				return ; //protect
		}
	}
	tmp[0] = ft_strdup(str);
	free(str);
	if (!tmp[0])
		return ; //protect
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
