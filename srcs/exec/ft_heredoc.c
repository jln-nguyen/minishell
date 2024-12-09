/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:31:34 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/09 15:13:03 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
static void	child_heredoc(t_ast_node *ast, int *fd)
{
	char	*line;

	close(fd[0]);
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
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	close(fd[1]);

}

static void	parent_heredoc(int *fd)
{
	int		status;

	close(fd[1]);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		else
			dup2(fd[0], 0);
	}
	close(fd[0]);
}


void	ft_heredoc(t_ast_node *ast)
{
	int	pid;
	int	fd[2];
	
	pipe(fd);
	pid = fork();
	if (!pid)
		child_heredoc(ast, fd);
	else
		parent_heredoc(fd);
}
