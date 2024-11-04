/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:15:22 by bvictoir          #+#    #+#             */
/*   Updated: 2024/11/04 14:40:51 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_check_end(char *str)
{
	if (!str)
		return (0);
	while (*str && *str != '\n')
		str++;
	if (*str == '\n')
		return (1);
	return (0);
}

static char	*ft_trim(char *line, char *buf)
{
	char	*rest;
	int		len_rest;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	len_rest = ft_strlen(line) - i;
	if (len_rest != 0)
		buf = ft_strcpy(buf, line + i);
	else
		buf[0] = '\0';
	rest = ft_substr(line, 0, i);
	free(line);
	return (rest);
}

static char	*ft_cpy_buf(char *str, char *buf)
{
	char	*tmp;
	int		len;

	len = 0;
	if (str)
		len = ft_strlen(str);
	tmp = ft_calloc(len + ft_strlen(buf) + 1, sizeof(char));
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	if (str)
	{
		tmp = ft_strcpy(tmp, str);
		tmp = ft_strcat(tmp, buf);
		free(str);
	}
	else
		tmp = ft_strcpy(tmp, buf);
	return (tmp);
}

static char	*ft_read(char *str, char *buf, int fd)
{
	int	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && ft_check_end(str) == 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		if (bytes_read == 0)
			return (str);
		else if (bytes_read < 0)
			return (free(str), NULL);
		str = ft_cpy_buf(str, buf);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buf[0] != '\0')
		line = ft_cpy_buf(line, buf);
	line = ft_read(line, buf, fd);
	if (!line)
		return (NULL);
	line = ft_trim(line, buf);
	if (!line)
	{
		line = ft_calloc(1, 1);
		if (!line)
			return (NULL);
	}
	return (line);
}
