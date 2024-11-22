/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:01:11 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/22 15:11:05 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_to_end_quote(char *str, char c)
{
	int	i;

	i = 0;
	i++;
	while (str[i] != c)
		i++;
	i++;
	return (i);
}

char	*change_str(char *new_str, int i)
{
	int		j;
	char	**tmp;

	tmp = NULL;
	if (new_str[i] == '\0' || new_str[i] == 34 || new_str[i] == 39 || new_str[i] == 32 || (new_str[i] >= 9 && new_str[i] <= 13))
		return (new_str);
	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		return (free(new_str), NULL);
	tmp[3] = 0;
	j = 0;
	while (new_str[i + j] != 32 && !(new_str[i + j] >= 9 && new_str[i + j] <= 13) && new_str[i + j] && new_str[i + j] != '$' && new_str[i + j] != 39 && new_str[i + j] != 34)
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

char	*check_expand_var(char *str, int i, int j)
{
	char	*new_str;

	new_str = NULL;
	new_str = ft_substr(str, i, j);
	if (!new_str)
		return (NULL);
	i = 0;
	while (new_str[i])
	{
		if (new_str[i] == '$')
		{
			new_str = change_str(new_str, i + 1);
			if (!new_str)
				return (NULL);
			if (new_str[i] == '\0')
				break ;
		}
		i++;
	}
	return (new_str);
}

char	*handle_double_quote(char *str, int i)
{
	int		j;
	char	**tmp;
	char	*new_str;

	j = 0;
	new_str = NULL;
	while (str[i + j + 1] && str[i + j + 1] != 34)
		j++;
	j += 2;
	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		return (free(new_str), NULL);
	tmp[3] = 0;
	tmp[0] = ft_substr(str, 0, i);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[1] = check_expand_var(str, i, j);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[2] = ft_substr(str, i + j, ft_strlen(str) - i - j);
	if (!tmp[2])
		return (ft_free_tab_var_env(&tmp), NULL);
	new_str = ft_strbigjoin(tmp[0], tmp[1], tmp[2]);
	if (!new_str)
		return (ft_free_tab_var_env(&tmp), NULL);
	return (ft_free_tab_var_env(&tmp), free(str), new_str);
}

char	*handle_quote(char *str, int i, int j)
{
	char	**tmp;
	char	*new_str;

	new_str = NULL;
	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		return (free(new_str), NULL);
	tmp[3] = 0;
	tmp[0] = ft_substr(str, 0, i - 1);
	if (!tmp[0])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[1] = ft_substr(str, i, j);
	if (!tmp[1])
		return (ft_free_tab_var_env(&tmp), NULL);
	tmp[2] = ft_substr(str, i + j + 1, ft_strlen(str) - i - j - 1);
	if (!tmp[2])
		return (ft_free_tab_var_env(&tmp), NULL);
	new_str = ft_strbigjoin(tmp[0], tmp[1], tmp[2]);
	if (!new_str)
		return (ft_free_tab_var_env(&tmp), NULL);
	return (ft_free_tab_var_env(&tmp), new_str);
}

char	*remove_quote(char *str, int i, char c)
{
	int		j;
	char	*new_str;

	j = 0;
	new_str = NULL;
	i++;
	while (str[i + j] && str[i + j] != c)
		j++;
	new_str = handle_quote(str, i, j);
	free(str);
	if (!new_str)
		return (NULL);
	return (new_str);
}

// t_token	*handle_quote(char *str)
// {
// 	int		i;
// 	char	*tmp;
// 	t_token	*tok;

// 	i = 0;
// 	tmp = NULL;
// 	while (str[i] != 39)
// 		i++;
// 	tmp = ft_substr(str, 0, i);
// 	if (!tmp)
// 		return (NULL);
// 	tok = new_tok(TOKEN_STR, tmp);
// 	free(tmp);
// 	return (tok);
// }

// t_token	*check_quote(char *str, char c)
// {
// 	char	*tmp;
// 	t_token	*tok;

// 	tmp = NULL;
// 	tok = NULL;
// 	if (c == 34)
// 	{
// 		tmp = handle_double_quote(str);
// 		if (!tmp)
// 			return (NULL);
// 		tok = new_tok(TOKEN_STR, tmp);
// 		free(tmp);
// 	}
// 	else
// 		tok = handle_quote(str);
// 	return (tok);
// }
