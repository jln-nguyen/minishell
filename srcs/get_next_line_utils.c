/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:27:15 by junguyen          #+#    #+#             */
/*   Updated: 2024/09/13 18:42:14 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	char	*array;
	size_t	i;

	i = 0;
	if (size * nmemb == 0)
	{
		array = malloc(0);
		return (array);
	}
	if (size > SIZE_MAX / nmemb)
		return (NULL);
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	while (i < nmemb * size)
	{
		array[i] = 0;
		i++;
	}
	return (array);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!dst || !src)
		return (NULL);
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_check_end(char *str)
{
	if (!str)
		return (0);
	while (*str && *str != '\n')
		str++;
	if (*str == '\n')
		return (1);
	return (0);
}
