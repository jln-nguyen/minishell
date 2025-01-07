/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:35 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/07 14:46:17 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_ast_node *ast, t_env **env)
{
	t_env	*tmp;

	if (!env)
		return (EXIT_FAILURE);
	else if (ast->right->args[1])
	{
		ft_printf(2, "too many argument\n");
		return (EXIT_FAILURE);
	}
	tmp = *env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
