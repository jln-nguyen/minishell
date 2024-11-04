/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifcspc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:05:45 by bvictoir          #+#    #+#             */
/*   Updated: 2024/09/18 22:11:12 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ifchar(va_list args, int count, int fd)
{
	char	c;

	c = va_arg(args, int);
	ft_putchar_fd(c, fd);
	count++;
	return (count);
}

int	ft_ifstring(va_list args, int count, int fd)
{
	char	*str;

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";
	count += ft_strlen(str);
	ft_putstr_fd(str, fd);
	return (count);
}

int	ft_ifpercent(int count, int fd)
{
	ft_putchar_fd('%', fd);
	count++;
	return (count);
}
