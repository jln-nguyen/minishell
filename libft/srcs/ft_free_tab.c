/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:47:05 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/29 14:05:00 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while ((*tab)[i])
	{
		if ((*tab)[i])
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
		i++;
	}
	free(*tab);
	*tab = NULL;
}
