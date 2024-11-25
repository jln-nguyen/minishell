/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:03:07 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/25 17:07:36 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab_var_env(char ***tab)
{
	free((*tab)[0]);
	free((*tab)[1]);
	free((*tab)[2]);
	free((*tab)[3]);
	free(*tab);
	*tab = NULL;
}

char	*ft_strbigjoin(const char *s1, const char *s2, const char *s3)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	str = (char *)malloc(len1 + len2 + len3 + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	ft_memcpy(str + len1 + len2, s3, len3);
	str[len1 + len2 + len3] = '\0';
	return (str);
}

char	*change_value(char *var)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	if (!var)
		return (NULL);
	tmp = getenv(var);
	if (!tmp)
		return (free(var), NULL);
	free(var);
	var = ft_strdup(tmp);
	return (var);
}

static void	sup_node_if(t_token **begin_list)
{
	t_token	*cur;

	cur = *begin_list;
	if (begin_list == NULL || *begin_list == NULL)
		return ;
	if (cur->value == NULL || cur->value[0] == '\0')
	{
		*begin_list = cur->next;
		if (cur->value)
			free(cur->value);
		free(cur);
		sup_node_if(begin_list);
	}
	else
	{
		cur = *begin_list;
		sup_node_if(&cur->next);
	}
}

int	move_index_quote(char *str, int i, char c)
{
	int		j;

	j = 0;
	while (str[i + j] && str[i + j] != c)
		j++;
	return (j);
}

char	*expand_var_env(char *new_str, int i)
{
	int		j;
	char	**tmp;

	tmp = NULL;
	if (new_str[i] == '\0')
		return (new_str);
	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		return (free(new_str), NULL);
	tmp[3] = 0;
	j = 0;
	while (new_str[i + j] && new_str[i + j] != '$' && new_str[i + j] != 39 && new_str[i + j] != 34)
		j++;
	tmp[0] = ft_substr(new_str, i, j);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	tmp[0] = change_value(tmp[0]);
	tmp[1] = ft_substr(new_str, 0, i - 1);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	tmp[2] = ft_substr(new_str, i + j, ft_strlen(new_str) - i - j);
	if (!tmp[2])
		return (ft_free_tab_var_env(&tmp), free(new_str), NULL);
	free(new_str);
	new_str = ft_strbigjoin(tmp[1], tmp[0], tmp[2]);
	if (!new_str)
		return (ft_free_tab_var_env(&tmp), NULL);
	return (ft_free_tab_var_env(&tmp), new_str);
}

void	change_value_if(t_token **tok)
{
	int	i;
	int	j;

	i = 0;
	while ((*tok)->value[i])
	{
		if ((*tok)->value[i] == 39 || (*tok)->value[i] == 34)
		{
			j = i;
			if ((*tok)->value[j] == 34)
				(*tok)->value = handle_double_quote((*tok)->value, j);
			i += move_index_quote((*tok)->value, i + 1, (*tok)->value[j]);
			(*tok)->value = remove_quote((*tok)->value, j, (*tok)->value[j]);
		}
		else if ((*tok)->value[i] == '$')
		{
			if ((*tok)->value[i + 1] == '\0')
				break ;
			(*tok)->value = expand_var_env((*tok)->value, i + 1);
		}
		else
			i++;
	}
}

t_token	*expand_str(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tok)
	{
		if (tok->type == TOKEN_STR || tok->type == TOKEN_ENV_VAR)
		{
			change_value_if(&tok);
			if (!tok->value)
				return (ft_free(&tok), NULL);
			tok->type = TOKEN_STR;
		}
		tok = tok->next;
	}
	tok = tmp;
	sup_node_if(&tok);
	return (tok);
}
