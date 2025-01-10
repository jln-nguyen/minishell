/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:46:44 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/10 16:27:10 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_child(t_ast_node **ast, t_env **env, int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (ast && *ast)
		ft_free_ast(ast);
	if (env && *env)
		ft_free_env(env);
	exit(EXIT_FAILURE);
}

static int	handle_left_pipe(t_ast_node **ast, t_env **env, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		// signal(SIGINT, SIG_DFL);
		// signal(SIGQUIT, SIG_DFL);
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			cleanup_child(ast, env, pipefd);
		}
		close(pipefd[1]);
		ft_exec(&((*ast)->left), env);
		ft_free_ast(ast);
		ft_free_env(env);
		exit(g_exit_status);
	}
	return (pid);
}

static int	handle_right_pipe(t_ast_node **ast, t_env **env, int *pipefd)
{
	pid_t	pid;

	// if ((*ast)->right->type == TOKEN_PIPE)
	// 	ft_exec(&(*ast)->right, env);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		// signal(SIGINT, SIG_DFL);
		// signal(SIGQUIT, SIG_DFL);
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			cleanup_child(ast, env, pipefd);
		}
		close(pipefd[0]);
		ft_exec(&((*ast)->right), env);
		ft_free_ast(ast);
		ft_free_env(env);
		exit(g_exit_status);
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
	left_pid = handle_left_pipe(ast, env, pipefd);
	if (left_pid == -1)
		return ((void)(close(pipefd[0]), close(pipefd[1])));
	right_pid = handle_right_pipe(ast, env, pipefd);
	if (right_pid == -1 && left_pid > 0)
		return ((void)(close(pipefd[0]), close(pipefd[1]), 
			waitpid(left_pid, NULL, 0)));
	close(pipefd[0]);
	close(pipefd[1]);
	if (left_pid > 0)
		waitpid(left_pid, NULL, 0);
	if (WIFEXITED(left_pid))
		g_exit_status = WEXITSTATUS(left_pid);
	if (right_pid > 0)
		waitpid(right_pid, NULL, 0);
	if (WIFEXITED(right_pid))
		g_exit_status = WEXITSTATUS(right_pid);
	ft_free_ast(ast);
}
