/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:02:35 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/29 15:54:57 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *str_key, char *str_val)
{
	t_env	*new;

	new = malloc(sizeof(new));
	if (!new)
		return (NULL);
	new->key = ft_strdup(str_key);
	if (!new->key)
		return (free(new), NULL);
	if (!str_val)
		new->value = NULL;
	else
	{
		new->value = ft_strdup(str_val);
		if (!new->value)
			return (free(new->key), free(new), NULL);
	}
	new->next = NULL;
	return (new);
}

int	expand_env(t_data *data, char *str_key, char *str_val)
{
	t_env	*new;

	new = new_env(str_key, str_val);
	if (!new)
		return (-1);
	ft_envadd_back(&data->env, new);
	return (0);
}

void	ft_create_env(t_data *data)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
		return ;
	data->env = new_env("OLDPWD", "");
	if (!data->env)
		return (free(buffer), (void)0);
	free(data->env->value);
	data->env->value = NULL;
	if (expand_env(data, "PWD", buffer) == -1)
		return (free(buffer), ft_free_env(&data->env), (void)0);
	if (expand_env(data, "SHLVL", "1") == -1)
		return (free(buffer), ft_free_env(&data->env), (void)0);
	if (expand_env(data, "_", "/usr/bin/env") == -1)
		return (free(buffer), ft_free_env(&data->env), (void)0);
	free(buffer);
}
