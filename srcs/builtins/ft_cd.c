/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:53:45 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/03 14:23:10 by bvictoir         ###   ########.fr       */
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

void	ft_cd(char *str, t_env **env)
{
	char	*pwd;
	char	*old_pwd;
	t_env	*tmp;

	old_pwd = getcwd(NULL, 0);
	if (chdir(str) < 0)
	{
		ft_printf(STDERR_FILENO, "Minishell: cd : %s: %s\n", str,
			strerror(errno));
		return (free(old_pwd));
	}
	pwd = getcwd(NULL, 0);
	tmp = *env;
	ft_change_wd(env, pwd, old_pwd);
	if (check_if_oldpwd(env) == 0)
		expand_env(env, "OLDPWD", old_pwd);
	return (free(old_pwd), free(pwd));
}
