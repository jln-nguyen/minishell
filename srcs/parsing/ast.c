/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:30:58 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/29 14:47:55 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_ast_node **lst, t_ast_node *new, char c)
{
	t_ast_node	*tmp;

	if (*lst == NULL)
		*lst = new;
	else if (c == 'L')
	{
		tmp = *lst;
		while (tmp->left != NULL)
			tmp = tmp->left;
		tmp->left = new;
	}
	else
	{
		tmp = *lst;
		while (tmp->right != NULL)
			tmp = tmp->right;
		tmp->right = new;
	}
}

int	expand_ast(t_ast_node **ast, t_token *tok, t_enum_type limit, char c)
{
	t_ast_node	*node;

	node = NULL;
	node = parsing_token(tok, limit);
	if (!node)
		return (-1);
	add_node(ast, node, c);
	return (0);
}

static int	if_pipe(t_token *tok, t_enum_type limit)
{
	while (tok && tok->type != limit)
	{
		if (tok->type == TOKEN_PIPE)
			return (1);
		tok = tok->next;
	}
	return (-1);
}

t_ast_node	*parsing_tok_next(t_token *tmp, t_token *tok, t_enum_type limit,
				t_ast_node *ast)
{
	if (tmp == NULL || tmp->type == TOKEN_STR || tmp->type == TOKEN_ENV_VAR)
		ast = parse_str(tok, limit);
	else if (tmp->type == TOKEN_REDIR_OUT || tmp->type == TOKEN_REDIR_APPEND
		|| tmp->type == TOKEN_REDIR_HEREDOC || tmp->type == TOKEN_REDIR_IN)
		ast = parse_redir_out(*tmp, tok);
	if (ast)
		return (ast);
	return (NULL);
}

t_ast_node	*parsing_token(t_token *tok, t_enum_type limit)
{
	t_ast_node	*ast;
	t_token		*tmp;

	tmp = tok;
	ast = NULL;
	if (!tok || tok->type == limit)
		return (NULL);
	if (if_pipe(tok, limit) == 1)
	{
		ast = check_pipe(tok, limit);
		if (ast)
			return (ast);
		return (NULL);
	}
	while (tmp && tmp->next && tmp->next->type != limit)
	{
		if (tmp->type != TOKEN_STR && tmp->type != TOKEN_ENV_VAR)
			break ;
		tmp = tmp->next;
	}
	ast = parsing_tok_next(tmp, tok, limit, ast);
	if (!ast)
		return (NULL);
	return (ast);
}
