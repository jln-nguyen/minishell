/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:56:38 by bvkm              #+#    #+#             */
/*   Updated: 2024/07/16 14:55:50 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **strs, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_strndup(const char *src, int s, int e)
{
	char	*dest;

	dest = malloc(sizeof(char) * (e - s + 1));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, &src[s], e - s + 1);
	dest[e - s] = '\0';
	return (dest);
}

static char	**ft_spliting(const char *str, char c, char **strs)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		j = i;
		while (str[j] && str[j] != c)
			j++;
		if (j != i)
		{
			strs[word] = ft_strndup(str, i, j);
			if (!strs[word])
				return (free_array(strs, word));
			word++;
		}
		i = j;
	}
	strs[word] = NULL;
	return (strs);
}

char	**ft_split(const char *str, char c)
{
	char	**strs;

	if (!str)
		return (NULL);
	strs = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!strs)
		return (NULL);
	return (ft_spliting(str, c, strs));
}
