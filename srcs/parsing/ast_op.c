/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:04:00 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/29 14:37:36 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*new_node(t_enum_type type)
{
	t_ast_node	*ast;

	ast = malloc(sizeof(t_ast_node));
	if (!ast)
		return (NULL);
	ast->type = type;
	ast->args = NULL;
	ast->left = NULL;
	ast->right = NULL;
	ast->fd_heredoc = 0;
	return (ast);
}

t_ast_node	*parse_pipe(t_token pipe, t_token *tok)
{
	t_ast_node	*ast;

	ast = NULL;
	ast = new_node(pipe.type);
	if (!ast)
		return (NULL);
	if (expand_ast(&ast, tok, TOKEN_PIPE, 'L') == -1)
		return (ft_free_ast(&ast), NULL);
	while (tok->type != pipe.type)
		tok = tok->next;
	tok = tok->next;
	if (expand_ast(&ast, &(*tok), -1, 'R') == -1)
		return (ft_free_ast(&ast), NULL);
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
			return (NULL);
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
	if (expand_ast(&ast, tok, op.type, 'L') == -1)
		return (ft_free_ast(&ast), NULL);
	while (tok->type != op.type)
		tok = tok->next;
	tok = tok->next;
	if (expand_ast(&ast, &(*tok), TOKEN_PIPE, 'R') == -1)
		return (ft_free_ast(&ast), NULL);
	return (ast);
}
