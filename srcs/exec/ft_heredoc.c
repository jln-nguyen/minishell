/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:31:34 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/12 13:55:22 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read(char *end, t_env **env, int fd)
{
	char	*line;
	int		i;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, end))
		{
			free(line);
			break ;
		}
		i = -1;
		while (line[++i])
			if (line[i] == '$')
				line = change_str(line, i + 1, *env);
		if (!line)
			return ; // protect
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

int	ft_heredoc(t_ast_node *ast, t_env **env)
{
	int		fd;

	fd = open("/tmp/.heredoc0", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	ft_read(ast->args[0], env, fd);
	close(fd);
	fd = open("/tmp/.heredoc0", O_RDONLY);
	if (fd < 0)
		return (-1);
	unlink("/tmp/.heredoc0");
	return (fd);
}
