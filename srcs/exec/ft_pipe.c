/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:46:44 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/20 13:55:30 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_pipe_left(t_ast_node **ast, t_env **env, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);
		ft_exec(&((*ast)->left), env);
		ft_free_ast(ast);
		ft_free_env(env);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

static int	exec_pipe_right(t_ast_node **ast, t_env **env, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
		if ((*ast)->right->type == TOKEN_PIPE)
			exec_pipe(&(*ast)->right, env);
		else
			ft_exec(&((*ast)->right), env);
		ft_free_ast(ast);
		ft_free_env(env);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

static int	init_pipe(int *pipefd, t_ast_node **ast)
{
	if (!ast || !*ast)
		return (0);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 0);
	return (1);
}

void	exec_pipe(t_ast_node **ast, t_env **env)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (!init_pipe(pipefd, ast))
		return ;
	left_pid = exec_pipe_left(ast, env, pipefd);
	if (left_pid == -1)
		return ((void)(close(pipefd[0]), close(pipefd[1])));
	right_pid = exec_pipe_right(ast, env, pipefd);
	if (right_pid == -1 && left_pid > 0)
		return ((void)(close(pipefd[0]), close(pipefd[1]), 
			waitpid(left_pid, NULL, 0)));
	close(pipefd[0]);
	close(pipefd[1]);
	if (left_pid > 0)
		waitpid(left_pid, NULL, 0);
	if (right_pid > 0)
		waitpid(right_pid, NULL, 0);
}
