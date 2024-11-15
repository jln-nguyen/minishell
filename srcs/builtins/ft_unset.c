/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:28 by bvictoir          #+#    #+#             */
/*   Updated: 2024/11/15 14:21:37 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove(t_env **env, t_token *tok)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, tok->value, ft_strlen(tok->value))
			&& !tmp->key[ft_strlen(tok->value)])
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

void	ft_unset(t_env **env, t_token *tok)
{
	if (!env || !tok->next)
		return ;
	tok = tok->next;
	while (tok)
	{
		ft_remove(env, tok);
		tok = tok->next;
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
// 	t_token *tok;

// 	tok = malloc(sizeof(t_token));
// 	tok->value = "unset";
// 	tok->next = NULL;
// 	tok->next = malloc(sizeof(t_token));
// 	tok->next->value = "";
// 	tok->next->next = NULL;
// 	tok->next->next = malloc(sizeof(t_token));
// 	tok->next->next->value = "SHLVL";
// 	tok->next->next->next = NULL;

// 	env_list = NULL;
// 	while (*env)
// 	{
// 		add_env(&env_list, *env);
// 		env++;
// 	}
// 	ft_unset(&env_list, tok);
// 	ft_env(env_list);
// 	return (0);
// }
