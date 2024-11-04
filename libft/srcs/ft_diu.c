/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:13:48 by bvictoir          #+#    #+#             */
/*   Updated: 2024/09/18 22:14:09 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ifdi(va_list args, int count, int fd)
{
	long	d;

	d = va_arg(args, int);
	if (d < 0)
	{
		ft_putchar_fd('-', fd);
		count++;
		d = -d;
	}
	ft_ltoa_base_fd(d, "0123456789", 10, fd);
	count += ft_printf_len(d, 10);
	return (count);
}

int	ft_ifu(va_list args, int count, int fd)
{
	unsigned int	u;
	char			*base;

	u = va_arg(args, unsigned int);
	base = "0123456789";
	ft_ltoa_base_fd(u, base, ft_strlen(base), fd);
	count += ft_printf_len(u, ft_strlen(base));
	return (count);
}
