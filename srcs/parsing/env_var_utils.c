/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:05:25 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/19 18:10:14 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char str)
{
	if (str == 32 || (str >= 9 && str <= 13))
		return (0);
	return (1);
}

void	ft_free_tab_var_env(char ***tab)
{
	free((*tab)[0]);
	free((*tab)[1]);
	free((*tab)[2]);
	free((*tab)[3]);
	free(*tab);
	*tab = NULL;
}

char	*ft_pre_bigjoin(char *new_str, char **tmp, int i, int j)
{
	tmp[2] = ft_substr(new_str, i + j, ft_strlen(new_str) - i - j);
	if (!tmp[2])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	free(new_str);
	new_str = ft_strbigjoin(tmp[1], tmp[0], tmp[2]);
	return (new_str);
}

char	*ft_strbigjoin(const char *s1, const char *s2, const char *s3)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	str = (char *)malloc(len1 + len2 + len3 + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	ft_memcpy(str + len1 + len2, s3, len3);
	str[len1 + len2 + len3] = '\0';
	return (str);
}

char	*change_value(char *var, t_env *env)
{
	char	*tmp;

	tmp = NULL;
	if (!var)
		return (NULL);
	if (var[0] == '?')
		return (free(var), tmp = ft_itoa(g_exit_status));
	while (env)
	{
		if (ft_strcmp(var, env->key) == 0)
		{
			tmp = ft_strdup(env->value);
			if (!tmp)
				return (NULL);
			return (free(var), tmp);
		}
		env = env->next;
	}
	return (free(var), NULL);
}
