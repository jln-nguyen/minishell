/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:05:25 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/22 18:23:26 by junguyen         ###   ########.fr       */
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

char	*get_value(t_env *env, t_data *data, t_token **head, char **split)
{
	char	*str;

	str = NULL;
	str = ft_strdup(env->value);
	if (!str)
	{
		ft_free_tab(&split);
		error_malloc_tok(head, data);
	}
	return (str);
}

char	*change_value(char *var, t_data *data, t_token **head, char **split)
{
	char	*tmp;
	t_env	*tmp_env;

	tmp = NULL;
	if (!var)
		return (NULL);
	tmp_env = data->env;
	if (var[0] == '?')
	{
		tmp = ft_itoa(data->exit_code);
		if (!tmp)
		{
			ft_free_tab(&split);
			error_malloc_tok(head, data);
		}
		return (free(var), tmp);
	}
	while (tmp_env)
	{
		if (ft_strcmp(var, tmp_env->key) == 0)
			tmp = get_value(tmp_env, data, head, split);
		tmp_env = tmp_env->next;
	}
	return (free(var), tmp);
}
