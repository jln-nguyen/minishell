/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:50:01 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/15 10:42:16 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_del_last(t_token *tok)
{
	t_token	*tmp;
	t_token	*courant;

	if (!tok)
		return (NULL);
	if (tok->next == NULL)
	{
		free(tok->value);
		free(tok);
		return (NULL);
	}
	courant = tok;
	while (courant->next != NULL)
	{
		tmp = courant;
		courant = courant->next;
	}
	tmp->next = courant->next;
	free(courant->value);
	free(courant);
	return (tok);
}

int	move_index(t_token *tok, char *str, int i)
{
	if (!tok)
		return (0);
	if (str[i] == 39 || str[i] == 34)
		return (move_to_end_quote(&str[i], str[i]));
	else
	{
		while (tok->next != NULL)
			tok = tok->next;
		return (ft_strlen(tok->value));
	}
}

void	ft_free(t_token **tok)
{
	t_token	*tmp;

	while (*tok != NULL)
	{
		tmp = (*tok)->next;
		free((*tok)->value);
		free(*tok);
		*tok = tmp;
	}
	*tok = NULL;
}

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

t_token	*new_tok(t_enum_type type, char *str)
{
	t_token	*element;

	element = NULL;
	element = malloc(sizeof(t_token));
	if (!element)
		return (NULL);
	element->type = type;
	element->value = ft_strdup(str);
	if (!element->value)
		return (NULL);
	element->next = NULL;
	return (element);
}
