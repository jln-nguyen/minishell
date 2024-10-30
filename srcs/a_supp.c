/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_supp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:53:16 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/30 15:53:31 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	print_token(t_token *tok)
{
	char	*type[7] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND",
		"HERE_DOC", "ENV"};
	char	*tmp;

	tmp = NULL;
	while (tok != NULL)
	{
		tmp = ft_strdup(type[tok->type]);
		printf("value : %s | type : %s\n", tok->value, tmp);
		free(tmp);
		tok = tok->next;
	}
}