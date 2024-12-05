/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:04:35 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/02 14:13:54 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_redirect(char *str, char c)
{
	int		i;
	char	d;

	i = 1;
	if (c == '<')
		d = '>';
	else
		d = '<';
	if (str[i] == c)
		i++;
	if (str[i] == c || str[i] == d)
	{
		ft_putstr_fd("Syntax error\n", STDERR_FILENO);
		return (0);
	}
	return (i);
}

static int	check_op(char *str, int i)
{
	int	j;

	j = 0;
	if (str[i] == '&' && str[i + 1] == '&')
		ft_putstr_fd("Non supported operators\n", STDERR_FILENO);
	else if (str[i] == '|')
	{
		if (str[i + 1] == '|')
			return (ft_putstr_fd("Non supported operators\n", STDERR_FILENO), 0);
		j++;
	}
	else if (str[i] == '>' || str[i] == '<')
		j += ft_check_redirect(&str[i], str[i]);
	return (j);
}

static int	check_end_quote(char *str, char c)
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

static int	check_invalid_char(char c)
{
	if (c == ';' || c == '\\' || c == '(' || c == ')' || c == '&')
		return (ft_putstr_fd("Invalid Character\n", STDERR_FILENO), -1);
	return (0);
}

int	check_syntax(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (check_invalid_char(str[i]) == -1)
			return (-1);
		if (str[i] == '\'' || str[i] == '"')
		{
			if (check_end_quote(&str[i], str[i]) == -1)
				return (-1);
			i += check_end_quote(&str[i], str[i]);
		}
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if (check_op(str, i) == 0)
				return (-1);
			i += check_op(str, i);
		}
		else
			i++;
	}
	return (0);
}
