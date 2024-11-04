/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifpxX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:05:49 by bvictoir          #+#    #+#             */
/*   Updated: 2024/09/18 22:13:24 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ifpointer(va_list args, int count, int fd)
{
	unsigned long long	pointer;
	char				*base;

	pointer = va_arg(args, unsigned long long);
	if (pointer == 0)
	{
		ft_putstr_fd("(nil)", fd);
		return (count + 5);
	}
	base = "0123456789abcdef";
	count += ft_printf_len(pointer, ft_strlen(base)) + 2;
	ft_putstr_fd("0x", fd);
	ft_ltoa_base_fd(pointer, base, ft_strlen(base), fd);
	return (count);
}

int	ft_ifhex(va_list args, int count, const char c, int fd)
{
	unsigned int	hex;
	char			*base;

	hex = va_arg(args, unsigned int);
	if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	ft_ltoa_base_fd(hex, base, ft_strlen(base), fd);
	count += ft_printf_len(hex, ft_strlen(base));
	return (count);
}
