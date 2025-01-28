/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:30:26 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/28 18:49:11 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_err(t_ast_node *ast, t_env **env)
{
	int	fd;
	
	fd = 3;
	ft_printf(STDERR_FILENO, "%s\n", strerror(errno));
	if (ast)
		ft_free_ast(&ast);
	if (env)
		ft_free_env(env);
	while (fd < 1024)
		close(fd++);
	exit(2);
}