/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:19:48 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/13 18:20:03 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_reset_fd(int old_fd_in, int old_fd_out)
{	
	if (old_fd_in != 0)
	{
		if (dup2(old_fd_in, STDIN_FILENO) == -1)
			return ((void)close(old_fd_in)); //return protect
		close(old_fd_in);
	}
	if (old_fd_out != 1)
	{
		if (dup2(old_fd_out, STDOUT_FILENO) == -1)
			return ((void)close(old_fd_out)); //return protect
		close(old_fd_out);
	}
}

static int	ft_dup_out(int file_out, int old_fd_out, int old_fd_in)
{
	if (file_out > 0)
	{
		old_fd_out = dup(STDOUT_FILENO);
		if (old_fd_out == -1)
			return (-1);
		if (dup2(file_out, STDOUT_FILENO) == -1)
			return (-1); //return protect
		close(file_out);
	}
	else if (file_out < 0)
	{
		g_signal = 1;
		ft_reset_fd(old_fd_in, old_fd_out);
		return (-1);
	}
	return (old_fd_out);
}

void	ft_redir(t_data data, t_ast_node **ast)
{
	int	old_fd_in;
	int	old_fd_out;
	int	file_in;
	int	file_out;

	old_fd_in = 0;
	old_fd_out = 1;
	search_cmd(ast);
	file_in = ft_redir_in(*ast, &data.env);
	if (file_in > 0)
	{
		old_fd_in = dup(STDIN_FILENO);
		if (old_fd_in == -1)
			return ;
		if (dup2(file_in, STDIN_FILENO) == -1)
			return ; //return protect
		close(file_in);
	}
	if (file_in < 0)
		return (data.exit_code = 1, ft_reset_fd(old_fd_in, old_fd_out));
	file_out = ft_redir_out(*ast);
	old_fd_out = ft_dup_out(file_out, old_fd_out, old_fd_in);
	if (old_fd_out == -1)
	{
		g_signal = 1;
		return ;
	}
	exec_cmd(data, &(*ast)->left);
	ft_reset_fd(old_fd_in, old_fd_out);
}
