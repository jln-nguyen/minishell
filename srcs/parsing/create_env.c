/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:02:35 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/10 13:42:27 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env	*new_env(char *str_key, char *str_val)
{
	t_env	*new;

	new = malloc(sizeof(new));
	if (!new)
		return (NULL);
	new->key = ft_strdup(str_key);
	if (!new->key)
		return (free(new), NULL);
	new->value = ft_strdup(str_val);
	if (!new->value)
		return (free(new->key), free(new), NULL);
	new->next = NULL;
	return (new);
}

int	expand_env(t_env **env, char *str_key, char *str_val)
{
	t_env	*new;

	new = new_env(str_key, str_val);
	if (!new)
		return (-1);
	ft_envadd_back(env, new);
	return (0);
}

t_env	*ft_create_env(void)
{
	t_env	*env;
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
		return (NULL);
	env = new_env("OLDPWD", "");
	if (!env)
		return (free(buffer), NULL);
	free(env->value);
	env->value = NULL;
	if (expand_env(&env, "PWD", buffer) == -1)
		return (free(buffer), ft_free_env(&env), NULL);
	if (expand_env(&env, "SHLVL", "1") == -1)
		return (free(buffer), ft_free_env(&env), NULL);
	if (expand_env(&env, "_", "/usr/bin/env") == -1)
		return (free(buffer), ft_free_env(&env), NULL);
	free(buffer);
	return (env);
}
