/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:08:17 by bvkm              #+#    #+#             */
/*   Updated: 2025/02/03 16:12:28 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_hd(t_data *data, char **tmp, char *file)
{
	ft_free_tab(&tmp);
	unlink(file);
	free(file);
	ft_err(data, "Malloc");
}

static char	*get_value_hd(t_env *env, t_data *data, char *file, char **tmp)
{
	char	*str;

	str = NULL;
	if (!env->value)
		return (NULL);
	str = ft_strdup(env->value);
	if (!str)
		ft_error_hd(data, tmp, file);
	return (str);
}

static char	*change_value_hd(char *var, t_data *data, char *file, char **split)
{
	char	*tmp;
	t_env	*tmp_env;

	tmp = NULL;
	if (!var)
		return (NULL);
	tmp_env = data->env;
	if (var[0] == '?')
	{
		tmp = ft_itoa(data->exit_code);
		if (!tmp)
			ft_error_hd(data, split, file);
		return (free(var), tmp);
	}
	while (tmp_env)
	{
		if (ft_strcmp(var, tmp_env->key) == 0)
			tmp = get_value_hd(tmp_env, data, file, split);
		tmp_env = tmp_env->next;
	}
	return (free(var), tmp);
}

char	*expand_heredoc(char *str, t_data *data, int *i, char *file)
{
	int		j;
	char	**tmp;

	tmp = NULL;
	*i += 1;
	if (str[*i] == '\0' || str[*i] == 34 || str[*i] == 39
		|| !ft_is_space(str[*i]))
		return (str);
	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		return (free(str), NULL);
	tmp[3] = 0;
	j = get_index(str, *i);
	tmp[0] = ft_substr(str, *i, j);
	if (!tmp[0])
		return (free(str), ft_error_hd(data, tmp, file), NULL);
	tmp[0] = change_value_hd(tmp[0], data, file, tmp);
	tmp[1] = ft_substr(str, 0, *i - 1);
	if (!tmp[1])
		return (free(str), ft_error_hd(data, tmp, file), NULL);
	str = ft_pre_bigjoin(str, tmp, *i, j);
	if (!str)
		ft_error_hd(data, tmp, file);
	*i += ft_strlen(tmp[0]) - 1;
	return (ft_free_tab_var_env(&tmp), str);
}

void	ft_break_here(char *line, char *end)
{
	if (g_signal == 130)
		return ;
	else if (!line)
	{
		ft_printf(STDERR_FILENO, "Minishell: warning: here-document delim");
		ft_printf(STDERR_FILENO, "ited by end-of-file (wanted `%s')\n", end);
	}
	else if (!ft_strcmp(line, end))
		free(line);
}
