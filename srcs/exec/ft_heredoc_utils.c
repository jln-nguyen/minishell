/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:08:17 by bvkm              #+#    #+#             */
/*   Updated: 2025/02/02 13:17:00 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_break_here(char *line, char *end)
{
	if (g_signal == 130)
		return ;
	else if (!line)
	{
		ft_printf(STDERR_FILENO, "Minishell: warning: here-document delim");
		ft_printf(STDERR_FILENO, "ited by end-of-file (wanted `%s')\n", end);
	}
	else if (!ft_strcmp(line, end))
		free(line);
}

int	redic_heredoc(t_ast_node *tmp, t_data *data, int *i)
{
	if (tmp->right->type == TOKEN_STR)
		tmp->fd_heredoc = ft_heredoc(tmp->right, data, *i);
	else
		tmp->fd_heredoc = ft_heredoc(tmp->right->left, data, *i);
	if (g_signal == 130)
		return (1);
	if (tmp->fd_heredoc < 0)
		return (ft_putstr_fd("error\n", STDERR_FILENO), 1); //?
	return (0);
}
