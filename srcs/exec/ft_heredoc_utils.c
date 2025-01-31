/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:08:17 by bvkm              #+#    #+#             */
/*   Updated: 2025/01/31 15:16:15 by bvkm             ###   ########.fr       */
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
