/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:53:45 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/29 17:26:19 by bvictoir         ###   ########.fr       */
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

static void	ft_change_wd(t_data *data, char *pwd, char *old_pwd)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->key, 6) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
			if (!tmp->value)
				(free(pwd), free(old_pwd), ft_malloc_err(data));
		}
		if (ft_strncmp("OLDPWD", tmp->key, 6) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(old_pwd);
			if (old_pwd &&!tmp->value)
				(free(pwd), free(old_pwd), ft_malloc_err(data));
		}
		tmp = tmp->next;
	}
}

static int	ft_cd_update(t_data *data, char *old_pwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_change_wd(data, pwd, old_pwd);
	free(old_pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

static int	ft_cd_home(t_data *data, char *old_pwd)
{
	t_env	*tmp;
	char	*home;

	tmp = data->env;
	home = NULL;
	while (tmp)
	{
		if (ft_strncmp("HOME", tmp->key, 6) == 0)
		{
			home = ft_strdup(tmp->value);
			if (!home)
				(free(old_pwd), ft_malloc_err(data));
		}
		tmp = tmp->next;
	}
	if (!home)
	{
		free(old_pwd);
		ft_printf(STDERR_FILENO, "Minishell: cd : HOME not set\n");
		return (EXIT_FAILURE);
	}
	chdir(home);
	free(home);
	return (EXIT_SUCCESS);
}

int	ft_cd(char **str, t_data *data)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (str[1] == NULL)
	{
		if (ft_cd_home(data, old_pwd))
			return (EXIT_FAILURE);
	}
	else if (str[2])
	{
		free(old_pwd);
		ft_printf(STDERR_FILENO, "Minishell: cd : too many arguments\n");
		return (EXIT_FAILURE);
	}
	else if (!str[1][0])
		return (ft_cd_update(data, old_pwd));
	else if (chdir(str[1]) < 0)
	{
		ft_printf(STDERR_FILENO, "Minishell: cd : %s: %s\n", str[1],
			strerror(errno));
		free(old_pwd);
		return (EXIT_FAILURE);
	}
	return (ft_cd_update(data, old_pwd));
}
