/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:15:22 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/07 14:16:55 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*array;
	size_t	i;

	i = 0;
	if (start + len > ft_strlen_gnl(s))
		len = ft_strlen_gnl(s) - start;
	if (start > ft_strlen_gnl(s))
		len = 0;
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	while (i < len && s[start])
		array[i++] = s[start++];
	array[i] = '\0';
	return (array);
}

char	*ft_trim(char *line, char *buf)
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
	len_rest = ft_strlen_gnl(line) - i;
	if (len_rest != 0)
		buf = ft_strcpy(buf, line + i);
	else
		buf[0] = '\0';
	rest = ft_substr_gnl(line, 0, i);
	free(line);
	return (rest);
}

char	*ft_cpy_buf(char *str, char *buf)
{
	char	*tmp;
	int		len;

	len = 0;
	if (str)
		len = ft_strlen_gnl(str);
	tmp = ft_calloc_gnl(len + ft_strlen_gnl(buf) + 1, sizeof(char));
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

char	*ft_read(char *str, char *buf, int fd)
{
	int		bytes_read;

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
		line = ft_calloc_gnl(1, 1);
		if (!line)
			return (NULL);
	}
	return (line);
}
