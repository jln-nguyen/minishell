/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:53:04 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/15 14:23:19 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_option(char *arg)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	if (arg[++i] == '-')
	{
		while (arg[++i])
		{
			n = 1;
			if (arg[i] != 'n')
			{
				n = 0;
				break ;
			}
		}
	}
	return (n);
}

int	ft_echo(char **args)
{
	int	n;
	int	i;

	i = 1;
	if (!args || !*args || !args[1])
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	n = ft_option(args[i]);
	while (args[i] && ft_option(args[i]))
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
	return (EXIT_SUCCESS);
}
