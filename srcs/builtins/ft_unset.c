/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:28 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/03 14:20:02 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key))
			&& !tmp->key[ft_strlen(key)])
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_env **env, t_ast_node *ast)
{
	int	i;

	i = 0;
	if (!env || !ast->args[1])
		return ;
	while (ast->args[++i])
	{
		ft_remove(env, ast->args[i]);
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
// 	ast->args[0] = "unset";
// 	ast->args[1] = "A";
// 	ast->args[2] = "test";

// 	env_list = NULL;
// 	while (*env)
// 	{
// 		add_env(&env_list, *env);
// 		env++;
// 	}
// 	ft_env(&env_list);
// 	ft_unset(&env_list, ast);
// 	ft_env(&env_list);

// 	return (0);
// }
