/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:53 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/20 15:39:58 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_atol(const char *str)
{
	int		i;
	long	num;
	long	signe;

	signe = 1;
	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (signe == -1)
		num *= signe;
	return (num);
}

int	ft_isvalid(char *n)
{
	long	i;
	int		signe;
	char	*tmp[3];

	i = 0;
	signe = 0;
	if (n[i] == '-')
	{
		i++;
		signe = -1;
	}
	while (n[i])
	{
		if (n[i] < '0' || n[i] > '9')
			return (-1);
		i++;
	}
	if (i >= 19 || (i >= 20 && signe == -1))
	{
		if (i > 19 || (i > 20 && signe == -1))
			return (-1);
		else
		{
			if (i == 19)
				tmp[0] = ft_substr(n, 0, 10);
			else
				tmp[0] = ft_substr(n, 0, 11);
			i = ft_atol(tmp[0]);
			if (i > 9223372036 || i < -9223372036)
				return (free(tmp[0]), -1);
			if (i == 9223372036 || i == -9223372036)
			{
				if (i == 19)
					tmp[1] = ft_substr(n, 10, ft_strlen(n));
				else
					tmp[1] = ft_substr(n, 11, ft_strlen(n));
				i = ft_atol(tmp[1]);
				if (i > 854775807 || (i > 854775808 && signe == -1))
					return (free(tmp[0]), free(tmp[1]), -1);
			}
			free(tmp[0]);
			free(tmp[1]);
		}
	}
	return (i);
}

void	ft_exit(char **args, t_ast_node **ast, t_env **env)
{
	(void)ast;
	(void)env;
	if (!args[1])
	{
		ft_free_ast(ast);
		ft_free_env(env);
		exit(EXIT_SUCCESS);
	}
	if (ft_isvalid(args[1]) == -1)
	{
		ft_printf(STDERR_FILENO, "Minishell: exit: %s: numeric argument required\n", args[1]);
		ft_free_ast(ast);
		ft_free_env(env);
		exit(EXIT_SUCCESS);
	}
	if (args[1] && args[2])
		ft_printf(STDERR_FILENO, "Minishell: exit: too many arguments\n");
}
