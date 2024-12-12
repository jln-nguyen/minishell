/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:31:34 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/12 10:47:08 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_read(char *end, t_env **env, int fd)
// {
// 	char	*line;
// 	int		i;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (!ft_strcmp(line, end))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		i = -1;
// 		while (line[++i])
// 			if (line[i] == '$')
// 				line = change_str(line, i + 1, *env);
// 		if (!line)
// 			return ; // protect
// 		ft_putstr_fd(line, fd);
// 		ft_putstr_fd("\n", fd);
// 		free(line);
// 	}
// }

// int	ft_heredoc(t_ast_node *ast, t_env **env)
// {
// 	int	fd;

// 	fd = open("/tmp/.heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fd < 0)
// 		return (-1);
// 	ft_read(ast->args[0], env, fd);
// 	close(fd);
// 	fd = open("/tmp/.heredoc", O_RDONLY);
// 	if (fd < 0)
// 		return (-1);
// 	unlink("/tmp/heredoc");
// 	return (fd);
// }

int	ft_heredoc(t_ast_node *ast, t_env **env)

{
	int		fd;
	int		i;
	char	*line;

	fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, ast->args[0]))
		{
			free(line);
			break ;
		}
		i = -1;
		while (line[++i])
			if (line[i] == '$')
				line = change_str(line, i + 1, *env);
		if (!line)
			exit(-1) ; // protect
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	fd = open("heredoc", O_RDONLY);
	unlink("heredoc");
	return (fd);
}