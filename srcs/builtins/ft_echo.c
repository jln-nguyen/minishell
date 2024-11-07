/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:53:04 by bvictoir          #+#    #+#             */
/*   Updated: 2024/11/07 10:55:13 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_option(t_token *tok)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	if (tok->value[++i] == '-')
	{
		while (tok->value[++i])
		{
			n = 1;
			if (tok->value[i] != 'n')
			{
				n = 0;
				break ;
			}
		}
	}
	return (n);
}

void	ft_echo(t_token *tok)
{
	int	n;

	if (!tok)
		return ((void) printf("\n"));
	n = ft_option(tok);
	if (n)
		tok = tok->next;
	while (tok)
	{
		if (tok->value)
			printf("%s", tok->value);
		if (tok->next)
			printf(" ");
		tok = tok->next;
	}
	if (!n)
		printf("\n");
}
