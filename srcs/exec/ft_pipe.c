/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:46:44 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/12 11:40:58 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_left_pipe(t_ast_node **ast, t_env **env, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		ft_exec(&((*ast)->left), env);
		exit(EXIT_FAILURE);
	}
}

static void	handle_right_pipe(t_ast_node **ast, t_env **env, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		ft_exec(&((*ast)->right), env);
		exit(EXIT_FAILURE);
	}
}

static void	wait_for_children(pid_t left_pid, pid_t right_pid)
{
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, NULL, 0);
}

void	exec_pipe(t_ast_node **ast, t_env **env)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	handle_left_pipe(ast, env, pipefd);
	handle_right_pipe(ast, env, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	wait_for_children(0, 0);
}
