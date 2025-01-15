/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:09 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/15 21:13:41 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_key(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (2);
}

static char	*ft_get_key(t_ast_node *ast, t_env **env, char *key, int i)
{
	key = ft_substr(ast->args[i], 0, ft_strchr(ast->args[i], '=')
			- ast->args[i]);
	if (ft_strchr(ast->args[i], '='))
		ft_update_env(env, key, ft_strchr(ast->args[i], '=') + 1, 1);
	else
		ft_update_env(env, key, NULL, 0);
	return (key);
}

static int	ft_process_arg(t_env **env, t_ast_node *ast, int i)
{
	char	*key;

	key = ft_substr(ast->args[i], 0, 2);
	if (!ft_strcmp(ast->args[i], "_") || !ft_strcmp(key, "_="))
	{
		free(key);
		return (EXIT_SUCCESS);
	}
	if (!ft_check_key(ast->args[i]))
	{
		printf("export: `%s': not a valid identifier\n", ast->args[i]);
		free(key);
		return (EXIT_FAILURE);
	}
	free(key);
	key = ft_get_key(ast, env, key, i);
	free(key);
	return (EXIT_SUCCESS);
}

static int	ft_exporting(t_env **env, t_ast_node *ast)
{
	int		i;
	int		status;
	char	*sub;

	i = 0;
	status = EXIT_SUCCESS;
	if (ast->args[1][0] == '-' && ast->args[1][1])
	{
		sub = ft_substr(ast->args[1], 0, 2);
		printf("export: %s: invalid option\n", sub);
		free(sub);
		return (2);
	}
	while (ast->args[++i])
	{
		if (ft_process_arg(env, ast, i) == EXIT_FAILURE)
			status = EXIT_FAILURE;
	}
	return (status);
}

int	ft_export(t_env **env, t_ast_node *ast)
{
	if (!ast->args[1])
	{
		ft_print_export(env);
		return (EXIT_SUCCESS);
	}
	else
		return (ft_exporting(env, ast));
}
