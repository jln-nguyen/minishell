/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:30:58 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/06 17:44:07 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free_ast(t_ast_node **tok)
{
	t_ast_node	*tmp;

	while (*tok != NULL)
	{
		tmp = (*tok)->right;
		free((*tok)->args);
		free(*tok);
		*tok = tmp;
	}
	*tok = NULL;
}

t_ast_node	*new_node(t_enum_type type, char *arg)
{
	t_ast_node	*ast;

	ast = NULL;
	ast = malloc(sizeof(t_ast_node));
	if (!ast)
		return (NULL);
	ast->type = type;
	ast->args = ft_strdup(arg);
	if (!ast->args)
		return (NULL);
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

// void	expand_ast_left(t_ast_node **ast, t_token *tok)
// {
// 	while (tok->type != (*ast)->type)
// 	{
// 		add_left_head(ast, tok);
// 		tok = tok->next;
// 	}
// }

// t_ast_node	*parse_pipe(t_token pipe, t_token *tok)
// {
// 	t_ast_node	*ast;

// 	ast = NULL;
// 	ast = new_node(pipe.type, pipe.value);
// 	if (!ast)
// 		return (NULL);
// 	expand_ast_left(&ast, tok);
// 	return (ast);
// }

void	add_right(t_ast_node **lst, t_token tok)
{
	t_ast_node	*tmp;
	t_ast_node	*new;

	new = NULL;
	new = new_node(tok.type, tok.value);
	if (!new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->right != NULL)
			tmp = tmp->right;
		tmp->right = new;
	}
}

t_ast_node	*parse_str(t_token *tok)
{
	t_ast_node	*head;
	t_ast_node	*node;

	head = NULL;
	node = NULL;
	head = new_node(tok->type, tok->value);
	if (!head)
		return (NULL);
	tok = tok->next;
	while (tok != NULL)
	{
		add_right(&head, *tok);
		tok = tok->next;
	}
	return (head);
}

t_ast_node	*parsing_token(t_token *tok)
{
	t_ast_node	*ast;
	t_token		*tmp;

	tmp = tok;
	ast = NULL;
	while (tok != NULL)
	{
		if (tok->type != TOKEN_STR)
			break ;
		tok = tok->next;
	}
	if (tok == NULL)
	{
		tok = tmp;
		ast = parse_str(tok);
	}
	else
	{
	if (tok->type == TOKEN_PIPE)
		// ast = parse_pipe(*tok, tok);
		printf("tqt\n");
	else if (tok->type == TOKEN_REDIR_HEREDOC)
		// ast = parse_heredoc();
		printf("tqt\n");
	else if (tok->type == TOKEN_REDIR_APPEND)
		// ast = parse_append();
		printf("tqt\n");
	else if (tok->type == TOKEN_REDIR_IN)
		// ast = parse_redir_in();
		printf("tqt\n");
	else if (tok->type == TOKEN_REDIR_OUT)
		// ast = parse_redir_out();
		printf("tqt\n");
	}
	return (ast);
}
