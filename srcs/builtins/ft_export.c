/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:09 by bvictoir          #+#    #+#             */
/*   Updated: 2024/11/15 15:13:04 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	order_tab(t_env **tab, t_env **env, int count)
{
	int		i;
	int		j;
	t_env	*tmp;

	tmp = *env;
	i = -1;
	while (tmp)
	{
		tab[++i] = tmp;
		tmp = tmp->next;
	}
	i = -1;
	while (++i < count)
	{
		j = i;
		while (++j < count)
		{
			if (ft_strcmp(tab[i]->key, tab[j]->key) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
}

void	ft_print_export(t_env **env)
{
	int	i;
	int	count;
	t_env	*tmp;
	t_env	**tab;

	count = 0;
	tmp = *env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(t_env *) * count);
	if (!tab)
		return ;
	order_tab(tab, env, count);
	i = -1;
	while (++i < count)
		printf("declare -x %s=\"%s\"\n", tab[i]->key, tab[i]->value);
	free(tab);
}

void	ft_export(t_env **env, t_token *tok)
{
	if (!tok->next)
		ft_print_export(env);
}


void	add_env(t_env **env, char *str)
{
	t_env	*new;
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return ;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_substr(str, 0, equal - str);
	new->value = ft_strdup(equal + 1);
	new->next = *env;
	*env = new;
}

int main(int ac, char **av, char **env)
{
	(void)ac, (void)av;
	t_env *env_list;
	t_token *tok;

	tok = malloc(sizeof(t_token));
	tok->value = "export";
	tok->next = NULL;
	tok->next = malloc(sizeof(t_token));
	tok->next->value = NULL;
	tok->next->next = NULL;
	// tok->next->next = malloc(sizeof(t_token));
	// tok->next->next->value = NULL;
	// tok->next->next->next = NULL;

	env_list = NULL;
	while (*env)
	{
		add_env(&env_list, *env);
		env++;
	}
	ft_export(&env_list, tok);
	// ft_env(&env_list);
	
	return (0);
}
