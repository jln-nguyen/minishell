/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:19:48 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/03 13:07:59 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_fd(t_data *data)
{
	if (data->old_fd_in != 0)
	{
		if (dup2(data->old_fd_in, STDIN_FILENO) == -1)
			(close(data->old_fd_in), ft_err(data, "dup2"));
		close(data->old_fd_in);
		data->old_fd_in = 0;
	}
	if (data->old_fd_out != 1)
	{
		if (dup2(data->old_fd_out, STDOUT_FILENO) == -1)
			(close(data->old_fd_out), ft_err(data, "dup2"));
		close(data->old_fd_out);
		data->old_fd_out = 1;
	}
}

static void	ft_dup_out(t_data *data)
{
	if (data->fd_out > 0)
	{
		data->old_fd_out = dup(STDOUT_FILENO);
		if (data->old_fd_out == -1)
			ft_err(data, "dup");
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			(close(data->fd_out), ft_err(data, "dup2"));
		close(data->fd_out);
	}
	else if (data->fd_out < 0)
		ft_reset_fd(data);
}

static void	fd_dup(t_data *data)
{
	if (data->fd_in > 0)
	{
		data->old_fd_in = dup(STDIN_FILENO);
		if (data->old_fd_in == -1)
			ft_err(data, "dup");
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			ft_err(data, "dup2");
		close(data->fd_in);
	}
}

void	ft_redir(t_data *data, t_ast_node **ast)
{
	search_cmd(ast, data);
	data->fd_in = ft_redir_in(*ast, &data->env);
	fd_dup(data);
	if (data->fd_in < 0)
		return (data->exit_code = 1, ft_reset_fd(data));
	data->fd_out = ft_redir_out(*ast);
	ft_dup_out(data);
	if (data->fd_out == -1)
	{
		data->exit_code = 1;
		return ;
	}
	exec_cmd(data, &(*ast)->left);
	ft_reset_fd(data);
}
