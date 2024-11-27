/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:02:35 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/26 18:26:14 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_env	*new_env(char *str_key, char *str_val)
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

static void	expand_env(t_env **env, char *str_key, char *str_val)
{
	t_env	*new;

	new = new_env(str_key, str_val);
	if (!new)
		return ; // protect
	ft_envadd_back(env, new);
}

t_env	*ft_create_env(void)
{
	t_env	*env;
	char	buffer[1024];

	getcwd(buffer, 1024);
	env = new_env("PWD", buffer);
	if (!env)
		return (NULL);
	expand_env(&env, "SHLVL", "1");
	expand_env(&env, "_", "/usr/bin/env");
	return (env);
}
