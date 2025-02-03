/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:05:06 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/03 11:57:57 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_cmd(char *cmd, char **envp, char *path)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		path = ft_strbigjoin(envp[i], "/", cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return ("\0");
}

static char	*find_path(char *cmd, char **env, t_data *data)
{
	int		i;
	char	*path;
	char	**envp;

	i = 0;
	envp = NULL;
	path = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			envp = ft_split(&env[i][5], ':');
			if (!envp || !*envp)
				(ft_free_tab(&env), ft_free_tab(&envp), ft_err(data, "Malloc"));
		}
		i++;
	}
	if (!envp || !*envp)
		return (NULL);
	path = check_cmd(cmd, envp, path);
	if (!path)
		(ft_free_tab(&env), ft_free_tab(&envp), ft_err(data, "Malloc"));
	ft_free_tab(&envp);
	return (path);
}

static void	ft_abs_path(t_data *data, t_ast_node **ast, char **env, char **path)
{
	if (access((*ast)->args[0], F_OK | X_OK) == 0)
	{
		*path = ft_strdup((*ast)->args[0]);
		if (!path)
		{
			ft_printf(STDERR_FILENO, "Malloc error\n");
			ft_free_tab(&env);
			(ft_free_ast(&data->ast), ft_free_env(&data->env));
			close_fds();
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_printf(STDERR_FILENO, "Minishell: %s: %s\n", (*ast)->args[0],
			strerror(errno));
		free(*path);
		ft_free_tab(&env);
		(ft_free_ast(&data->ast), ft_free_env(&data->env));
		close_fds();
		if (errno == 13)
			exit(126);
		exit(127);
	}
}

void	ft_process(char **env, t_ast_node **ast, t_data *data)
{
	char	*path;

	path = NULL;
	close_fds();
	if (ft_strnstr((*ast)->args[0], "/", ft_strlen((*ast)->args[0])) != NULL)
		ft_abs_path(data, ast, env, &path);
	else
		path = find_path((*ast)->args[0], env, data);
	if (!path || path[0] == '\0' || (*ast)->args[0][0] == '\0')
		ft_no_path(data, ast, env, path);
	execve(path, (*ast)->args, env);
	ft_printf(STDERR_FILENO, "Minishell: %s: Is a directory\n",
		(*ast)->args[0]);
	free(path);
	ft_free_tab(&env);
	ft_free_ast(&data->ast);
	ft_free_env(&data->env);
	close_fds();
	exit(126);
}

int	ft_execve(char **env, t_ast_node **ast, t_data *data)
{
	int	pid;
	int	exit_code;

	exit_code = 0;
	pid = fork();
	signal(SIGINT, &sigint_process);
	signal(SIGQUIT, &sigint_process);
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		ft_process(env, ast, data);
		ft_reset_fd(data);
	}
	else
		wait(&pid);
	if (WIFEXITED(pid))
		exit_code = WEXITSTATUS(pid);
	else if (WIFSIGNALED(pid))
		exit_code = 128 + WTERMSIG(pid);
	return (exit_code);
}
