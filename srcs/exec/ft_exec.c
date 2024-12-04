/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:03:36 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/04 10:30:44 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_size(t_env *env)
{
	int	i;
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
	tab = malloc(sizeof(char *) * (ft_env_size(env) + 1));
	if (!*tab)
		return (NULL);
	tab[i] = 0;
	i = 0;
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
	return (tab);
}

void	exec_cmd(t_ast_node *ast, t_env **env)
{
	if (ft_strncmp("cd", ast->args[0], 2) == 0)
		ft_cd(ast->args[1], env);
	else if (ft_strncmp("env", ast->args[0], 3) == 0)
		ft_env(env);
	else if (ft_strncmp("pwd", ast->args[0], 3) == 0)
		ft_pwd();
	else if (ft_strncmp("echo", ast->args[0], 4) == 0)
		ft_echo(ast->args);
	else if (ft_strncmp("export", ast->args[0], 6) == 0)
		printf("export\n"); //mettre export
	else if (ft_strncmp("unset", ast->args[0], 5) == 0)
		printf("unset\n"); //mettre unset
	else if (ft_strncmp("exit", ast->args[0], 4) == 0)
		printf("exit\n"); //mettre exit
	else
		printf("exec\n"); //faire exec
}

void	ft_exec(t_ast_node *ast, t_env **env)
{
	if (ast->type == TOKEN_PIPE)
		printf("pipe\n");
		// exec_pipe(ast->left, ast->right);
	else
		exec_cmd(ast, env);
}
