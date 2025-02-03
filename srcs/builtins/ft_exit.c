/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:54:53 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/29 18:03:01 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_long_lims(char *n, t_data *data, int signe, char *tmp[2])
{
	long	i;

	if (signe == 0)
		tmp[1] = ft_substr(n, 10, ft_strlen(n));
	else
		tmp[1] = ft_substr(n, 11, ft_strlen(n));
	if (!tmp[1])
		(free(n), free(tmp[0]), ft_err(data, "Malloc"));
	i = ft_atol(tmp[1]);
	if ((i > 854775807 && (signe == 0 || signe == 1)) || (i > 854775808
			&& signe == -1))
	{
		free(tmp[0]);
		free(tmp[1]);
		ft_end(data, -1, n);
	}
	free(tmp[0]);
	free(tmp[1]);
}

static void	handle_long_num(char *n, t_data *data, int signe, long len)
{
	char	*tmp[2];
	long	i;

	if (len == 19)
		tmp[0] = ft_substr(n, 0, 10);
	else
		tmp[0] = ft_substr(n, 0, 11);
	if (!tmp[0])
		(free(n), ft_err(data, "Malloc"));
	i = ft_atol(tmp[0]);
	if (i > 9223372036 || i < -9223372036)
	{
		free(tmp[0]);
		ft_end(data, -1, n);
	}
	if (i == 9223372036 || i == -9223372036)
		check_long_lims(n, data, signe, tmp);
	else
		free(tmp[0]);
}

static long	ft_isnum(char *n, t_data *data, long i, int signe)
{
	check_sign(n, data, &i, &signe);
	while (n[i])
	{
		if (!n[i] || n[i] < '0' || n[i] > '9')
			ft_end(data, -1, n);
		i++;
	}
	if ((i >= 20 && signe == 1) || (i >= 19 && signe == 0) || (i >= 20
			&& signe == -1))
	{
		if ((i > 20 && signe == -1) || (i > 19 && signe == 0) || (i > 20
				&& signe == 1))
			ft_end(data, -1, n);
		else
			handle_long_num(n, data, signe, i);
	}
	return (ft_atol(n));
}

static char	*ft_supp_before_zero(char *n, t_data *data)
{
	size_t	start;
	size_t	end;
	char	*str;
	char	sign;

	if (!n)
		return (ft_strdup(""));
	start = 0;
	sign = 0;
	if (n[start] == '+' || n[start] == '-')
	{
		sign = n[start];
		start++;
	}
	while (n[start] && n[start] == '0')
		start++;
	end = ft_strlen(n);
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!str)
		ft_err(data, "Malloc");
	if (sign)
		str[0] = sign;
	ft_strlcpy(str + (sign != 0), n + start, end - start + 1);
	return (str);
}

void	ft_exit(t_data *data, char **args)
{
	long	nb;
	char	*tmp;

	if (!args[1])
		ft_end(data, 0, NULL);
	tmp = ft_supp_before_zero(args[1], data);
	if (!tmp)
		ft_err(data, "Malloc");
	nb = ft_isnum(tmp, data, 0, 0);
	free(tmp);
	if (args[1] && args[2])
	{
		data->exit_code = 1;
		ft_printf(STDERR_FILENO, "Minishell: exit: too many arguments\n");
		return ;
	}
	if (nb >= 0 && nb <= 255)
		data->exit_code = nb;
	else
		data->exit_code = nb % 256;
	ft_end(data, 0, NULL);
}
