/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:04:35 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/12 17:44:50 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_check_redirect(char *str, char c)
{
	int	i;

	i = 1;
	if (str[i] == c)
		i++;
	if (str[i] == c)
	{
		ft_putstr_fd("Invalid redirection\n", STDERR_FILENO);
		return (0);
	}
	return (i);
}

int	check_op(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '&' && str[i + 1] == '&')
		ft_putstr_fd("Non supported operators\n", STDERR_FILENO);
	else if (str[i] == '|')
	{
		if (str[i + 1] == '|')
			ft_putstr_fd("Non supported operators\n", STDERR_FILENO);
		else
			i++;
			// ft_check_place_pipe(&str[i]);
	}
	else if (str[i] == '>' || str[i] == '<')
		i += ft_check_redirect(&str[i], str[i]);
		//check_place_redirect
	return (i);
}

int	check_end_quote(char *str, char c)
{
	int	i;

	i = 1;
	if (!str[i])
	{
		ft_putstr_fd("Non closed quote\n", STDERR_FILENO);
		return (-1);
	}
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	ft_putstr_fd("Non closed quote\n", STDERR_FILENO);
	return (-1);
}

int	check_syntax(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] == ';' || str[i] == '\\')
			return (ft_putstr_fd("Invalid Character\n", STDERR_FILENO), -2);
		if (str[i] == '\'' || str[i] == '"')
		{
			if (check_end_quote(&str[i], str[i]) == -1)
				return (-1);
			i += check_end_quote(&str[i], str[i]);
		}
		if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&')
		{
			if (check_op(&str[i]) == 0)
				return (-1);
			i += check_op(&str[i]);
		}
		else
			i++;
	}
	return (0);
}
