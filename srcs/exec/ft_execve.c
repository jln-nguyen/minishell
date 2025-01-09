/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:05:06 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/07 14:43:28 by junguyen         ###   ########.fr       */
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
	return (NULL);
}

char	*find_path(char *cmd, char **env)
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
				return (NULL);
		}
		i++;
	}
	if (!envp || !*envp)
		return (NULL);
	path = check_cmd(cmd, envp, path);
	ft_free_tab(&envp);
	return (path);
}

void	ft_process(char **env, t_ast_node **ast, t_env **envp)
{
	char	*path;

	path = NULL;
	if (ft_strnstr((*ast)->args[0], "/", ft_strlen((*ast)->args[0])) != NULL)
	{
		if (access((*ast)->args[0], F_OK | X_OK) == 0)
		{
			path = ft_strdup((*ast)->args[0]);
			if (!path)
			{
				ft_printf(STDERR_FILENO, "Malloc error\n");
				free(path);
				ft_free_tab(&env);
				ft_free_ast(ast);
				ft_free_env(envp);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			ft_printf(STDERR_FILENO, "Minishell: %s: No such file or directory\n", (*ast)->args[0]);
			free(path);
			ft_free_tab(&env);
			ft_free_ast(ast);
			ft_free_env(envp);
			exit(127);
		}
	}
	else
		path = find_path((*ast)->args[0], env);
	if (path == NULL)
	{
		ft_printf(STDERR_FILENO, "Minishell: %s: command not found\n", (*ast)->args[0]);
		free(path);
		ft_free_tab(&env);
		ft_free_ast(ast);
		ft_free_env(envp);
		exit(127);
	}
	execve(path, (*ast)->args, env);
	ft_printf(STDERR_FILENO, "Minishell: %s: Is a directory\n", (*ast)->args[0]);
	free(path);
	ft_free_tab(&env);
	ft_free_ast(ast);
	ft_free_env(envp);
	exit(126);
}

void	ft_execve(char **env, t_ast_node **ast, t_env **envp)
{
	int	pid;

	pid = fork();
	signal(SIGINT, &sigint_process);
	signal(SIGQUIT, &sigint_process);
	if (pid == -1)
		return ;
	if (pid == 0)
		ft_process(env, ast, envp);
	else
		wait(&pid);
	if (WIFEXITED(pid))
		g_exit_status = WEXITSTATUS(pid);
	return ;
}

