/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:55:30 by bvictoir          #+#    #+#             */
/*   Updated: 2024/09/18 22:15:03 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <limits.h>
# include <stdarg.h>

void	ft_ltoa_base_fd(unsigned long long n, char *base, int base_len, int fd);

int		ft_ifpercent(int count, int fd);
int		ft_ifu(va_list args, int count, int fd);
int		ft_printf(int fd, const char *str, ...);
int		ft_ifdi(va_list args, int count, int fd);
int		ft_ifchar(va_list args, int count, int fd);
int		ft_ifstring(va_list args, int count, int fd);
int		ft_ifpointer(va_list args, int count, int fd);
int		ft_printf_len(unsigned long long n, int len_base);
int		ft_ifhex(va_list args, int count, const char c, int fd);
int		ft_cspdiuxpc(va_list args, int count, const char c, int fd);

#endif