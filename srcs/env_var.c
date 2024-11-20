/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:03:07 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/20 18:01:48 by junguyen         ###   ########.fr       */
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
	if (cur->value == NULL)
	{
		*begin_list = cur->next;
		free(cur);
		sup_node_if(begin_list);
	}
	else
	{
		cur = *begin_list;
		sup_node_if(&cur->next);
	}
}

// t_token	*expand_var(t_token *tok)
// {
// 	t_token	*tmp;
// 	char	*value;

// 	tmp = tok;
// 	while (tok != NULL)
// 	{
// 		if (tok->type == TOKEN_ENV_VAR)
// 		{
// 			value = handle_double_quote(tok->value);
// 			if (!value)
// 				return (ft_free(&tmp), NULL);
// 			free(tok->value);
// 			tok->value = ft_strdup(value);
// 			free(value);
// 			tok->type = TOKEN_STR;
// 		}
// 		tok = tok->next;
// 	}
// 	tok = tmp;
// 	sup_node_if(&tok);
// 	return (tok);
// }

t_token	*expand_str(t_token *tok)
{
	int		i;
	char	*value;
	t_token	*tmp;

	tmp = tok;
	i = 0;
	while (tok)
	{
		if (tok->type == TOKEN_STR || tok->type == TOKEN_ENV_VAR)
		{
			while (tok->value[i])
			{
				// if (tok->value[i] == 34)
				// 	handle_double_quote();
				if (tok->value[i] == 39)
				{
					value = handle_quote(tok->value);
					free(tok->value);
					tok->value = ft_strdup(value);
					free(value);
				}
				// else if (tok->value[i] == '$')
				// 	expand_var();
				else
					i++;
			}
		}
		tok = tok->next;
	}
	tok = tmp;
	sup_node_if(&tok);
	return (tok);
}
