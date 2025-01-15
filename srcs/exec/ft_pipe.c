/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:46:44 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/15 13:07:58 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_child(t_data *data, int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (data->ast)
		ft_free_ast(&data->ast);
	if (data->env)
		ft_free_env(&data->env);
	exit(EXIT_FAILURE);
}

static int	handle_left_pipe(t_data *data, t_ast_node **ast, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, sigint_process);
		signal(SIGQUIT, sigint_process);
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			cleanup_child(data, pipefd);
		}
		close(pipefd[1]);
		ft_exec(data, &(*ast)->left);
		ft_free_ast(&data->ast);
		ft_free_env(&data->env);
		exit(data->exit_code);
	}
	return (pid);
}

static int	handle_right_pipe(t_data *data, t_ast_node **ast, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			cleanup_child(data, pipefd);
		}
		close(pipefd[0]);
		ft_exec(data, &(*ast)->right);
		ft_free_ast(&data->ast);
		ft_free_env(&data->env);
		exit(data->exit_code);
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

void	exec_pipe(t_data *data, t_ast_node **ast)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	status = 0;
	if (!init_pipe(pipefd, ast))
		return ;
	left_pid = handle_left_pipe(data, ast, pipefd);
	if (left_pid == -1)
		return ((void)(close(pipefd[0]), close(pipefd[1])));
	right_pid = handle_right_pipe(data, ast, pipefd);
	if (right_pid == -1 && left_pid > 0)
		return ((void)(close(pipefd[0]), close(pipefd[1]), 
			waitpid(left_pid, NULL, 0)));
	close(pipefd[0]);
	close(pipefd[1]);
	if (left_pid > 0)
		waitpid(left_pid, NULL, 0);
	if (right_pid > 0)
		waitpid(right_pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_code = 128 + WTERMSIG(status);
}
