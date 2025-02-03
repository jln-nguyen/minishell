/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:53:38 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/03 11:06:11 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	while (*env != NULL)
	{
		tmp = (*env)->next;
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		if (*env)
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

static int	ft_expand_env(t_data *data, char **envp, int i)
{
	t_env	*node;

	node = NULL;
	node = new_node_env(envp[i]);
	if (!node)
		return (-1);
	ft_envadd_back(&data->env, node);
	return (0);
}

void	ft_getenv(t_data *data, char **envp)
{
	int		i;

	i = 0;
	data->env = new_node_env(envp[i]);
	if (!data->env)
		return ;
	i++;
	while (envp[i])
	{
		if (ft_expand_env(data, envp, i) == -1)
			return (ft_free_env(&data->env), (void)0);
		i++;
	}
}
