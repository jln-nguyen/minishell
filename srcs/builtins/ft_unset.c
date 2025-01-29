/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:28 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/29 10:35:42 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key))
			&& !tmp->key[ft_strlen(key)])
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			(free(tmp->key), free(tmp->value), free(tmp));
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_env **env, t_ast_node *ast)
{
	int	i;

	i = 0;
	if (!env || !ast->args[1])
		return ;
	while (ast->args[++i])
	{
		ft_remove(env, ast->args[i]);
	}
}
