/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:19:48 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/02 13:23:23 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_fd(int old_fd_in, int old_fd_out, t_data *data)
{
	if (old_fd_in != 0)
	{
		if (dup2(old_fd_in, STDIN_FILENO) == -1)
			 (close(old_fd_in), ft_err(data, "dup2"));
		close(old_fd_in);
	}
	if (old_fd_out != 1)
	{
		if (dup2(old_fd_out, STDOUT_FILENO) == -1)
			(close(old_fd_out), ft_err(data, "dup2"));
		close(old_fd_out);
	}
}

static int	ft_dup_out(int file_out, int old_fd_out, int old_fd_in, t_data *data)
{
	if (file_out > 0)
	{
		old_fd_out = dup(STDOUT_FILENO);
		if (old_fd_out == -1)
			ft_err(data, "dup");
		if (dup2(file_out, STDOUT_FILENO) == -1)
			(close(file_out), ft_err(data, "dup2"));
		close(file_out);
	}
	else if (file_out < 0)
	{
		ft_reset_fd(old_fd_in, old_fd_out, data);
		return (-1);
	}
	return (old_fd_out);
}

void	ft_redir(t_data *data, t_ast_node **ast)
{
	int	old_fd_in;
	int	old_fd_out;
	int	file_in;
	int	file_out;

	old_fd_in = 0;
	old_fd_out = 1;
	search_cmd(ast, data);
	file_in = ft_redir_in(*ast, &data->env);
	if (file_in > 0)
	{
		old_fd_in = dup(STDIN_FILENO);
		if (old_fd_in == -1)
			ft_err(data, "dup");
		if (dup2(file_in, STDIN_FILENO) == -1)
			ft_err(data, "dup2");
		close(file_in);
	}
	if (file_in < 0)
		return (data->exit_code = 1, ft_reset_fd(old_fd_in, old_fd_out, data));
	file_out = ft_redir_out(*ast);
	old_fd_out = ft_dup_out(file_out, old_fd_out, old_fd_in, data);
	if (old_fd_out == -1)
	{
		data->exit_code = 1;
		return ;
	}
	data->fd_in = file_in;
	data->fd_out = file_out;
	data->old_fd_in = old_fd_in;
	data->old_fd_out = old_fd_out;
	exec_cmd(data, &(*ast)->left);
	ft_reset_fd(old_fd_in, old_fd_out, data);
}
