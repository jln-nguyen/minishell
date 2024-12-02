/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:09 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/02 12:01:58 by junguyen         ###   ########.fr       */
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

void	ft_export(t_env **env, t_token *tok)
{
	char	*key;

	if (!tok->next)
		ft_print_export(env);
	else
	{
		tok = tok->next;
		while (tok)
		{
			if (!ft_check_key(tok->value))
				printf("export: `%s': not a valid identifier\n", tok->value);
			else
			{
				key = ft_substr(tok->value, 0, ft_strchr(tok->value, '=')
						- tok->value);
				if (ft_strchr(tok->value, '='))
					ft_update_env(env, key, ft_strchr(tok->value, '=') + 1, 1);
				else
					ft_update_env(env, key, NULL, 0);
			}
			tok = tok->next;
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
// 	t_token *tok;

// 	tok = malloc(sizeof(t_token));
// 	tok->value = "export";
// 	tok->next = NULL;
// 	tok->next = malloc(sizeof(t_token));
// 	tok->next->value = "d=";
// 	tok->next->next = NULL;
// 	tok->next->next = malloc(sizeof(t_token));
// 	tok->next->next->value = "e=42";
// 	tok->next->next->next = NULL;

// 	env_list = NULL;
// 	while (*env)
// 	{
// 		add_env(&env_list, *env);
// 		env++;
// 	}
// 	ft_export(&env_list, tok);
// 	ft_env(&env_list);

// 	return (0);
// }