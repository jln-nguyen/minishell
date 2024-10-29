/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:50:01 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/29 18:56:25 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	ft_tokadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*new_tok(int type, char *str)
{
	t_token	*element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->type = type;
	element->value = str;
	element->next = NULL;
	return (element);
}
