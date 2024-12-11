/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:31:34 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/11 11:26:09 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_heredoc(int write_fd, const char *eof, t_env **env)
{
	char	*line;
	int		i;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		i = -1;
		while (line[++i])
			if (line[i] == '$')
				line = change_str(line, i + 1, *env);
		ft_putstr_fd(line, write_fd);
		ft_putstr_fd("\n", write_fd);
		free(line);
	}
	close(write_fd);
	exit(0);
}

static int	parent_heredoc(int read_fd)
{
	int		fd;
	char	buff[4096];
	ssize_t	bytes_read;

	fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		exit(1); // protect
	while ((bytes_read = read(read_fd, buff, sizeof(buff))) > 0)
		write(fd, buff, bytes_read);
	close(read_fd);
	close(fd);
	fd = open("/tmp/heredoc", O_RDONLY);
	if (fd == -1)
		exit(1); // protect
	return (fd);
}

int	ft_heredoc(t_ast_node *ast, t_env **env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit(1); // protect
	pid = fork();
	if (pid == -1)
		exit(1); // protect
	if (pid == 0)
	{
		close(fd[0]);
		child_heredoc(fd[1], ast->args[0], env);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		unlink("/tmp/heredoc");
		return (parent_heredoc(fd[0]));
	}
	return (-1);
}

// int	ft_heredoc(t_ast_node *ast)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("Error: ", 2);
// 		ft_putstr_fd(strerror(errno), 2);
// 		ft_putstr_fd("\n", 2);
// 		return (-1);
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (!ft_strcmp(line, ast->args[0]))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_putstr_fd(line, fd);
// 		ft_putstr_fd("\n", fd);
// 		free(line);
// 	}
// 	close(fd);
// 	fd = open("heredoc", O_RDONLY);
// 	return (fd);
// }
