/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:02:46 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/29 19:08:57 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
		close(fd++);
}

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
	close_fds();
	exit(EXIT_FAILURE);
}

void	ft_err(t_data *data, char *str)
{
	ft_printf(STDERR_FILENO, "Minishell: %s error\n", str);
	if (data->ast)
		ft_free_ast(&data->ast);
	if (data->env)
		ft_free_env(&data->env);
	close_fds();
	exit(EXIT_FAILURE);
}
