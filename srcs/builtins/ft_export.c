/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:09 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/09 17:52:53 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	return (1);
}

static void	ft_update_env(t_env **env, char *key, char *value, int bool)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	while (tmp && bool)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = NULL;
	if (value)
		new->value = ft_strdup(value);
	new->next = NULL;
	tmp->next = new;
}

void	ft_export(t_env **env, t_ast_node *ast)
{
	char	*key;
	int		i;

	i = 0;
	if (!ast->args[1])
		ft_print_export(env);
	else
	{
		while (ast->args[++i])
		{
			if (!ft_check_key(ast->args[i]))
				printf("export: `%s': not a valid identifier\n", ast->args[i]);
			else
			{
				key = ft_substr(ast->args[i], 0, ft_strchr(ast->args[i], '=')
						- ast->args[i]);
				if (ft_strchr(ast->args[i], '='))
					ft_update_env(env, key, ft_strchr(ast->args[i], '=') + 1,
						1);
				else
					ft_update_env(env, key, NULL, 1); //pourquoi le booleen ?
				free(key);
			}
		}
	}
}

// void	add_env(t_env **env, char *str)
// {
// 	t_env	*new;
// 	char	*equal;

// 	equal = ft_strchr(str, '=');
// 	if (!equal)
// 		return ;
// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return ;
// 	new->key = ft_substr(str, 0, equal - str);
// 	new->value = ft_strdup(equal + 1);
// 	new->next = *env;
// 	*env = new;
// }
// int main(int ac, char **av, char **env)
// {
// 	(void)ac, (void)av;
// 	t_env *env_list;
// 	t_ast_node *ast;

// 	ast = malloc(sizeof(t_ast_node));
// 	ast->args = malloc(sizeof(char *) * 4);
// 	ast->args[0] = "export";
// 	ast->args[1] = "VAR=42";
// 	ast->args[2] = "VAR2=42";

// 	env_list = NULL;
// 	while (*env)
// 	{
// 		add_env(&env_list, *env);
// 		env++;
// 	}
// 	ft_export(&env_list, ast);
// 	ast->args[1] = NULL;
// 	ft_export(&env_list, ast);
// 	// ft_env(&env_list);

// 	return (0);
// }