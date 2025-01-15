/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:35 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/15 15:38:12 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_ast_node *ast, t_env **env)
{
	t_env	*tmp;

	if (!env)
		return (EXIT_FAILURE);
	else if (ast->args[1])
	{
		ft_printf(2, "too many argument\n");
		return (127);
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
