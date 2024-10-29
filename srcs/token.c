/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:24:48 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/29 20:50:13 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	print_token(t_token *tok)
{
	printf("%s | type : %s\n", tok->value, tok->value);
}

void	ft_token(char *str)
{
	int		i;
	t_token	*tok;
	char	*tmp;

	i = 0;
	tmp = NULL;
	tok = NULL;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '|')
		{
			tmp = ft_strdup("|");
			tok = new_tok(1, tmp);
			free(tmp);
		}
		else if (str[i] == '<')
		{
			tmp = ft_strdup("<");
			tok = new_tok(2, tmp);
			free(tmp);
		}
		else if (str[i] == '>')
		{
			tmp = ft_strdup(">");
			tok = new_tok(3, tmp);
			free(tmp);
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			tmp = ft_strdup(">>");
			tok = new_tok(4, tmp);
			free(tmp);
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			tmp = ft_strdup("<<");
			tok = new_tok(5, tmp);
			free(tmp);
		}
	}
}
