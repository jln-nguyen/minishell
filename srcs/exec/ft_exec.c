/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:03:36 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/09 17:18:54 by junguyen         ###   ########.fr       */
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

int	ft_check_builtins(t_ast_node *ast, t_env **env)
{
	if (ft_strcmp("cd", ast->args[0]) == 0)
		return (ft_cd(ast->args[1], env), 0);
	else if (ft_strcmp("env", ast->args[0]) == 0)
		return (ft_env(env), 0);
	else if (ft_strcmp("pwd", ast->args[0]) == 0)
		return (ft_pwd(), 0);
	else if (ft_strcmp("echo", ast->args[0]) == 0)
		return (ft_echo(&ast->args[1]), 0);
	else if (ft_strcmp("export", ast->args[0]) == 0)
		return (ft_export(env, ast), 0);
	else if (ft_strcmp("unset", ast->args[0]) == 0)
		return (printf("unset\n"), 0); //mettre unset
	else if (ft_strcmp("exit", ast->args[0]) == 0)
		return (printf("exit\n"), 0); //mettre exit
	return (-1);
}

void	exec_cmd(t_ast_node **ast, t_env **env)
{
	char	**tab;

	tab = NULL;
	if (!*ast || !ast)
		return ;
	if ((*ast)->type != TOKEN_STR)
		ft_redir(ast, env);
	else if (!*(*ast)->args || !(*ast)->args[0])
		return ;
	else if (ft_check_builtins(*ast, env) == -1)
	{
		tab = struc_to_char(*env);
		if (!tab || !*tab)
			return ; //protect
		ft_execve(tab, (*ast)->args);
		ft_free_tab(&tab);
	}
}

void	ft_exec(t_ast_node **ast, t_env **env)
{
	if ((*ast)->type == TOKEN_PIPE)
		printf("pipe\n");
		// exec_pipe(ast->left, ast->right);
	else
		exec_cmd(ast, env);
}
