/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:04:00 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/25 16:05:13 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast_node	*parse_pipe(t_token pipe, t_token *tok)
{
	t_ast_node	*ast;

	ast = NULL;
	ast = new_node(pipe.type);
	if (!ast)
		return (NULL);
	expand_ast(&ast, tok, TOKEN_PIPE, 'L');
	while (tok->type != pipe.type)
		tok = tok->next;
	tok = tok->next;
	expand_ast(&ast, &(*tok), -1, 'R');
	return (ast);
}

t_ast_node	*check_pipe(t_token *tok, t_enum_type limit)
{
	t_ast_node	*ast;
	t_token		*tmp;

	tmp = tok;
	ast = NULL;
	while (tmp && tmp->next && tmp->next->type != limit)
	{
		if (tmp->type == TOKEN_PIPE)
			break ;
		tmp = tmp->next;
	}
	if (tmp->type == TOKEN_PIPE)
	{	
		ast = parse_pipe(*tmp, tok);
		if (!ast)
			return (NULL); //exit fn
		return (ast);
	}
	return (NULL);
}

t_ast_node	*parse_redir_out(t_token op, t_token *tok)
{
	t_ast_node	*ast;

	ast = NULL;
	ast = new_node(op.type);
	if (!ast)
		return (NULL);
	expand_ast(&ast, tok, op.type, 'L');
	while (tok->type != op.type)
		tok = tok->next;
	tok = tok->next;
	expand_ast(&ast, &(*tok), TOKEN_PIPE, 'R');
	return (ast);
}
