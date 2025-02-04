/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:02:46 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/03 16:11:54 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(void)
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
	if (tok)
		ft_free(tok);
	if (data->env)
		ft_free_env(&data->env);
	ft_printf(STDERR_FILENO, "Minishell: Malloc error\n");
	close_fds();
	rl_clear_history();
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
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	ft_free_ast(t_ast_node **ast)
{
	int	i;

	i = 0;
	if (!ast || !*ast)
		return ;
	ft_free_ast(&(*ast)->left);
	ft_free_ast(&(*ast)->right);
	if ((*ast)->args)
	{
		while ((*ast)->args[i])
			free((*ast)->args[i++]);
		free((*ast)->args);
	}
	if ((*ast)->fd_heredoc > 0)
		close((*ast)->fd_heredoc);
	free(*ast);
	*ast = NULL;
}
