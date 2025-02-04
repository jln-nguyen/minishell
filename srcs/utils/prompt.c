/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:00:55 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/04 16:31:02 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_home(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

char	*get_home(t_env *env)
{
	char	*str;

	str = NULL;
	while (env)
	{
		if (ft_strcmp("HOME", env->key) == 0)
			str = ft_strdup(env->value);
		env = env->next;
	}
	return (str);
}

char	*color_gwd(char *gwd, t_data *data)
{
	char	*home;
	char	*tmp;

	tmp = NULL;
	home = NULL;
	if (check_home(data->env) == 1)
	{
		home = get_home(data->env);
		if (!home)
			return (free(gwd), NULL);
		tmp = ft_substr(gwd, ft_strlen(home), ft_strlen(gwd));
		free(gwd);
		if (!tmp)
			return (free(home), NULL);
		gwd = ft_strjoin("~", tmp);
		free(tmp);
		free(home);
		if (!gwd)
			return (NULL);
	}
	tmp = ft_strbigjoin("\001\033[0;36m\033[1m\002", gwd, "\001\033[0m\002");
	free(gwd);
	return (tmp);
}

char	*get_prompt(t_data *data)
{
	char	*tmp;
	char	*gwd;

	gwd = NULL;
	tmp = NULL;
	tmp = getcwd(NULL, 0);
	// if (!tmp)
	// 	error_malloc_tok(NULL, data);
	gwd = ft_strjoin(tmp, "$ ");
	free(tmp);
	if (!gwd)
		error_malloc_tok(NULL, data);
	gwd = color_gwd(gwd, data);
	if (!gwd)
		error_malloc_tok(NULL, data);
	return (gwd);
}
