/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:53:45 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/14 18:29:36 by junguyen         ###   ########.fr       */
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

int	ft_cd(char *str, t_data *data)
{
	char	*pwd;
	char	*old_pwd;

	if (!str)
		return (EXIT_FAILURE); // exit tout free
	old_pwd = getcwd(NULL, 0);
	if (chdir(str) < 0)
	{
		ft_printf(STDERR_FILENO, "Minishell: cd : %s: %s\n", str,
			strerror(errno));
		free(old_pwd);
		return (EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	ft_change_wd(&data->env, pwd, old_pwd);
	if (check_if_oldpwd(&data->env) == 0)
		expand_env(data, "OLDPWD", old_pwd);
	free(old_pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
