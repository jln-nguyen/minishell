/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:53 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/15 12:22:49 by junguyen         ###   ########.fr       */
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

void	ft_end(t_data *data, int n, char *arg)
{
	ft_printf(STDOUT_FILENO, "exit\n");
	if (n == -1)
	{
		data->exit_code = 2;
		ft_printf(STDERR_FILENO, "Minishell: exit: %s: numeric argument required\n", arg);
	}
	ft_free_ast(&data->ast);
	ft_free_env(&data->env);
	exit(data->exit_code);
}

long	ft_isvalid(char *n, t_data *data)
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
		if (!n[i] || n[i] < '0' || n[i] > '9')
			ft_end(data, -1, n);
		i++;
	}
	if ((i >= 19 && signe == 0) || (i >= 20 && signe == -1))
	{
		if ((i > 20 && signe == -1) || (i > 19 && signe == 0))
			ft_end(data, -1, n);
		else
		{
			if (i == 19)
				tmp[0] = ft_substr(n, 0, 10);
			else
				tmp[0] = ft_substr(n, 0, 11);
			i = ft_atol(tmp[0]);
			if (i > 9223372036 || i < -9223372036)
			{
				free(tmp[0]);
				ft_end(data, -1, n);
			}
			if (i == 9223372036 || i == -9223372036)
			{
				if (signe == 0)
					tmp[1] = ft_substr(n, 10, ft_strlen(n));
				else
					tmp[1] = ft_substr(n, 11, ft_strlen(n));
				i = ft_atol(tmp[1]);
				if ((i > 854775807 && signe == 0) || (i > 854775808 && signe == -1))
				{
					free(tmp[0]);
					free(tmp[1]);
					ft_end(data, -1, n);
				}
			}
			free(tmp[0]);
			free(tmp[1]);
		}
	}
	return (ft_atol(n));
}

void	ft_exit(t_data *data, char **args)
{
	// int		i;
	long	nb;

	// i = 0;
	if (!args[1])
		ft_end(data, 0, NULL);
	nb = ft_isvalid(args[1], data);
	if (args[1] && args[2])
		return (data->exit_code = 1, (void)ft_printf(STDERR_FILENO, "Minishell: exit: too many arguments\n"));
	if (nb >= 0 && nb <= 255)
		data->exit_code = nb;
	else
		data->exit_code = nb % 256;
	ft_end(data, 0, NULL);
}
