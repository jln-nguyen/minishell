/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:05:06 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/02 17:41:41 by junguyen         ###   ########.fr       */
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

static char	*find_path(char *cmd, char **env)
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

void	ft_process(char **env, char **cmd)
{
	char	*path;

	path = NULL;
	if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])) != NULL)
	{
		if (access(cmd[0], F_OK | X_OK) == 0)
		{
			path = ft_strdup(cmd[0]);
			if (!path)
				return ; //protect
		}
		else
			return ; //protect
	}
	else
		path = find_path(cmd[0], env);
	if (path == NULL)
	{
		ft_printf(STDERR_FILENO, "Minishell: %s: command not found\n", cmd[0]);
		return ; //protect
	}
	execve(path, cmd, env);
	free(path);
	return ; //protect
}

void	ft_execve(char **env, char **cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		ft_process(env, cmd);
	else
		wait(&pid);
	return ;
}

