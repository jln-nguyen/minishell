/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:53:45 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/21 15:18:16 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_oldpwd(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp("OLDPWD", tmp->key, 6) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_change_wd(t_env **env, char *pwd, char *old_pwd)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->key, 6) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		if (ft_strncmp("OLDPWD", tmp->key, 6) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(old_pwd);
		}
		if (!tmp->value)
			return ; // exit fn free et tout
		tmp = tmp->next;
	}
}

static char	*get_home(t_env **env)
{
	t_env	*tmp;
	char	*home;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp("HOME", tmp->key, 6) == 0)
		{
			home = ft_strdup(tmp->value);
			return (home);
		}
		tmp = tmp->next;
	}
	return (NULL);	
}

static int	ft_cd_update(t_data *data)
{	
	char	*pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	pwd = getcwd(NULL, 0);
	ft_change_wd(&data->env, pwd, old_pwd);
	if (check_if_oldpwd(&data->env) == 0)
		expand_env(data, "OLDPWD", old_pwd);
	free(old_pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}


int	ft_cd(char **str, t_data *data)
{
	char	*home;

	if (str[1] == NULL)
	{
		home = get_home(&data->env);
		if (!home)
		{
			ft_printf(STDERR_FILENO, "Minishell: cd : HOME not set\n");
			return (EXIT_FAILURE);
		}
		chdir(home);
		free(home);
	}
	else if (str[2])
	{
		ft_printf(STDERR_FILENO, "Minishell: cd : too many arguments\n");
		return (EXIT_FAILURE);
	}
	else if (!str[1][0])
		return (EXIT_SUCCESS);
	else if (chdir(str[1]) < 0)
	{
		ft_printf(STDERR_FILENO, "Minishell: cd : %s: %s\n", str[1],
			strerror(errno));
		return (EXIT_FAILURE);
	}
	return (ft_cd_update(data));
}
