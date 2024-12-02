/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:53:04 by bvictoir          #+#    #+#             */
/*   Updated: 2024/11/28 17:41:35 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_option(char **args)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	if (args[0][++i] == '-')
	{
		while (args[0][++i])
		{
			n = 1;
			if (args[0][i] != 'n')
			{
				n = 0;
				break ;
			}
		}
	}
	return (n);
}

void	ft_echo(char **args)
{
	int	n;
	int	i;

	i = 0;
	if (!args)
		return ((void) printf("\n"));
	n = ft_option(args);
	if (n)
		i++;
	while (args[i])
	{
		if (args[i])
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
}
