/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:19:55 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/15 21:14:56 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	order_tab(t_env **tab, t_env **env, int count)
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

static void	ft_is_print(t_env *tab)
{
	if (ft_strcmp(tab->key, "_") == 0)
		return ;
	if (!tab->value)
		printf("export %s\n", tab->key);
	else
		printf("export %s=\"%s\"\n", tab->key, tab->value);
}

void	ft_print_export(t_env **env)
{
	int		i;
	int		count;
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
		ft_is_print(tab[i]);
	free(tab);
}

static void	ft_add_env(t_env *tmp, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = NULL;
	if (value)
		new->value = ft_strdup(value);
	new->next = tmp->next;
	tmp->next = new;
}

void	ft_update_env(t_env **env, char *key, char *value, int bool)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (bool)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return ;
		}
		if (!ft_strcmp(tmp->next->key, "_"))
			break ;
		tmp = tmp->next;
	}
	ft_add_env(tmp, key, value);
}
