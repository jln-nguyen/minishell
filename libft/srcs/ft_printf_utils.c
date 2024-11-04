/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:59:34 by bvictoir          #+#    #+#             */
/*   Updated: 2024/09/18 22:15:51 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_len(unsigned long long n, int len_base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / len_base;
		len++;
	}
	return (len);
}

void	ft_ltoa_base_fd(unsigned long long n, char *base, int base_len, int fd)
{
	if (n >= (unsigned long long )base_len)
	{
		ft_ltoa_base_fd(n / base_len, base, base_len, fd);
		ft_putchar_fd(base[n % base_len], fd);
	}
	else
		ft_putchar_fd(base[n], fd);
}

int	ft_cspdiuxpc(va_list args, int count, const char c, int fd)
{
	if (c == 'c')
		count = ft_ifchar(args, count, fd);
	else if (c == 's')
		count = ft_ifstring(args, count, fd);
	else if (c == 'p')
		count = ft_ifpointer(args, count, fd);
	else if (c == 'd' || c == 'i')
		count = ft_ifdi(args, count, fd);
	else if (c == 'u')
		count = ft_ifu(args, count, fd);
	else if (c == 'x' || c == 'X')
		count = ft_ifhex(args, count, c, fd);
	else if (c == '%')
		count = ft_ifpercent(count, fd);
	return (count);
}
