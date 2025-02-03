/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:08:34 by bvictoir          #+#    #+#             */
/*   Updated: 2025/02/03 14:42:06 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_no_path(t_data *data, t_ast_node **ast, char **env, char *path)
{
	ft_printf(STDERR_FILENO, "Minishell: %s: command not found\n",
		(*ast)->args[0]);
	if (path && path[0])
		free(path);
	ft_free_tab(&env);
	ft_free_ast(&data->ast);
	ft_free_env(&data->env);
	close_fds();
	exit(127);
}
