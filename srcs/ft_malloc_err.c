/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:30:26 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/28 19:25:41 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_err(t_data *data)
{
	int	fd;
	
	fd = 3;
	ft_printf(STDERR_FILENO, "%s\n", strerror(errno));
	if (data->ast)
		ft_free_ast(&data->ast);
	if (data->env)
		ft_free_env(&data->env);
	while (fd < 1024)
		close(fd++);
	exit(2);
}