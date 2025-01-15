/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:03:36 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/15 18:04:47 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_size(t_env *env)
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

char	**struc_to_char(t_env *env)
{
	char	**tab;
	int		i;

	i = 0;
	tab = NULL;
	tab = malloc(sizeof(char *) * (ft_env_size(env) + 1));
	if (!tab)
		return (NULL);
	while (env)
	{
		tab[i] = ft_strbigjoin(env->key, "=", env->value);
		if (!tab[i])
		{
			ft_free_tab(&tab);
			return (NULL);
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
		return (ft_cd(ast->args[1], data));
	else if (ft_strcmp("env", ast->args[0]) == 0)
		return (ft_env(ast, env));
	else if (ft_strcmp("pwd", ast->args[0]) == 0)
		return (ft_pwd(ast));
	else if (ft_strcmp("echo", ast->args[0]) == 0)
		return (ft_echo(ast->args));
	else if (ft_strcmp("export", ast->args[0]) == 0)
		return (ft_export(env, ast));
	else if (ft_strcmp("unset", ast->args[0]) == 0)
		return (ft_unset(env, ast), 0);
	else if (ft_strcmp("exit", ast->args[0]) == 0)
		return (ft_exit(data, ast->args), 0); //remettre data.exit
	return (-1);
}

void	exec_cmd(t_data *data, t_ast_node **ast)
{
	// int		status;
	char	**tab;

	tab = NULL;
	if (!*ast || !ast)
		return ;
	if ((*ast)->type != TOKEN_STR)
		ft_redir(data, ast);
	else if (!*(*ast)->args || !(*ast)->args[0])
		return ;
	else 
	{
		data->exit_code = ft_check_builtins(data, (*ast), &data->env);
		if (data->exit_code == -1)
		{
		tab = struc_to_char(data->env);
		if (!tab || !*tab)
			return ; //protect
		data->exit_code = ft_execve(tab, ast, data);
		ft_free_tab(&tab);
		}
	}
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

