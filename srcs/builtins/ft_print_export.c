/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:19:55 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/02 12:01:51 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		printf("export %s=\"%s\"\n", tab[i]->key, tab[i]->value);
	free(tab);
}
