/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:02:46 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/29 13:35:02 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab_var_env(char ***tab)
{
	free((*tab)[0]);
	free((*tab)[1]);
	free((*tab)[2]);
	free((*tab)[3]);
	free(*tab);
	*tab = NULL;
}

void	error_malloc_tok(t_token **tok, t_data *data)
{
	ft_free(tok);
	ft_free_env(&data->env);
	ft_printf(STDERR_FILENO, "Minishell: Malloc error\n");
	exit(EXIT_FAILURE);
}

void	ft_malloc_err(t_data *data)
{
	int	fd;
	
	fd = 3;
	ft_printf(STDERR_FILENO, "Minishell : Malloc error\n");
	if (data->ast)
		ft_free_ast(&data->ast);
	if (data->env)
		ft_free_env(&data->env);
	while (fd < 1024)
		close(fd++);
	exit(2);
}