/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:03:36 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/04 10:47:14 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_env_size(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!env)
		return (0);
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**struc_to_char(t_env *env, t_data *data)
{
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_env_size(env) + 1));
	if (!tab)
		ft_err(data, "Malloc error");
	while (env)
	{
		tab[i] = ft_strbigjoin(env->key, "=", env->value);
		if (!tab[i])
		{
			ft_free_tab(&tab);
			ft_err(data, "Malloc error");
		}
		i++;
		env = env->next;
	}
	tab[i] = 0;
	return (tab);
}

int	ft_check_builtins(t_data *data, t_ast_node *ast, t_env **env)
{
	if (ft_strcmp("cd", ast->args[0]) == 0)
		return (ft_cd(ast->args, data));
	else if (ft_strcmp("env", ast->args[0]) == 0)
		return (ft_env(ast, env));
	else if (ft_strcmp("pwd", ast->args[0]) == 0)
		return (ft_pwd(data, ast));
	else if (ft_strcmp("echo", ast->args[0]) == 0)
		return (ft_echo(ast->args));
	else if (ft_strcmp("export", ast->args[0]) == 0)
		return (ft_export(data, env, ast));
	else if (ft_strcmp("unset", ast->args[0]) == 0)
		return (ft_unset(env, ast), 0);
	else if (ft_strcmp("exit", ast->args[0]) == 0)
		return (ft_exit(data, ast->args), data->exit_code);
	return (-1);
}

void	ft_exec(t_data *data, t_ast_node **ast)
{
	if ((*ast)->type == TOKEN_PIPE)
		exec_pipe(data, ast);
	else
		exec_cmd(data, ast);
}

void	ft_check_heredoc(t_ast_node **ast, t_data *data)
{
	check_heredoc(ast, data);
	if (g_signal == 130)
	{
		g_signal = 0;
		data->exit_code = 130;
		return ;
	}
	ft_exec(data, &data->ast);
}
