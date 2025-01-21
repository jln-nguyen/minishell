/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:07:33 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/21 10:04:24 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_end(t_data *data, int n, char *arg)
{
	int	fd;

	fd = 3;
	ft_printf(STDOUT_FILENO, "exit\n");
	if (n == -1)
	{
		data->exit_code = 2;
		ft_printf(STDERR_FILENO,
			"Minishell: exit: %s: numeric argument required\n", arg);
	}
	free(arg);
	ft_free_ast(&data->ast);
	ft_free_env(&data->env);
	while (fd < 1024)
		close(fd++);
	exit(data->exit_code);
}

void	check_sign(char *n, t_data *data, long *i, int *signe)
{
	if (n[*i] == '+' || n[*i] == '-')
	{
		if (n[*i] == '-')
			*signe = -1;
		if (n[*i] == '+')
			*signe = 1;
		if (n[*i + 1] == '+' || n[*i + 1] == '-')
			ft_end(data, -1, n);
		(*i)++;
	}
}

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
