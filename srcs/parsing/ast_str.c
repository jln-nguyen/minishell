/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:59:50 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/20 15:53:00 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strlen_tok(t_token *tok, t_enum_type limit)
{
	int	i;

	i = 0;
	if (!tok)
		return (0);
	while (tok && tok->type != limit)
	{
		i++;
		tok = tok->next;
	}
	return (i);
}

static void	ft_fill_args(t_ast_node **head, t_token *tok, t_enum_type limit)
{
	int	i;

	i = 0;
	while (tok && tok->type != limit)
	{
		(*head)->args[i] = ft_strdup(tok->value);
		if (!(*head)->args[i])
		{
			while (i > 0)
				free((*head)->args[--i]);
			free((*head)->args);
			(*head)->args = NULL;
			return ; //protect
		}
		i++;
		tok = tok->next;
	}
	(*head)->args[i] = 0;
}

t_ast_node	*parse_str(t_token *tok, t_enum_type limit)
{
	t_ast_node	*head;
	int			len;

	len = ft_strlen_tok(tok, limit);
	head = NULL;
	head = new_node(tok->type);
	if (!head)
		return (NULL);
	head->args = malloc(sizeof(char *) * (len + 1));
	if (!head->args)
		return (free(head), NULL);
	ft_fill_args(&head, tok, limit);
	if (!head->args)
		return (free(head), NULL);
	return (head);
}
