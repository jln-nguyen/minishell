/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:53:38 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/27 18:03:13 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	while (*env != NULL)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
	*env = NULL;
}

void	ft_envadd_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_env	*new_node_env(char *envp)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	while (envp[i] != '=')
		i++;
	node->key = malloc(sizeof(char) * (i + 1));
	if (!node->key)
		return (free(node), NULL);
	ft_strlcpy(node->key, envp, i + 1);
	if (envp[0] == '_')
		node->value = ft_strdup("/usr/bin/env");
	else
		node->value = ft_strdup(&envp[i + 1]);
	if (!node->value)
		return (free(node->key), free(node), NULL);
	node->next = NULL;
	return (node);
}

static int	ft_expand_env(t_env **env, char **envp, int i)
{
	t_env	*node;

	node = NULL;
	node = new_node_env(envp[i]);
	if (!node)
		return (-1);
	ft_envadd_back(env, node);
	return (0);
}

t_env	*ft_getenv(char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	env = new_node_env(envp[i]);
	if (!env)
		return (NULL);
	i++;
	while (envp[i])
	{
		if (ft_expand_env(&env, envp, i) == -1)
			return (ft_free_env(&env), NULL);
		i++;
	}
	return (env);
}
