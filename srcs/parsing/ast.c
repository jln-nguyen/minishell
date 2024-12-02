/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:30:58 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/28 13:46:19 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_ast(t_ast_node **ast)
{
	int	i;

	i = 0;
	if (!*ast)
		return ;
	ft_free_ast(&(*ast)->left);
	ft_free_ast(&(*ast)->right);
	if ((*ast)->args)
	{
		while ((*ast)->args[i])
			i++;
		while (i-- > 0)
			free((*ast)->args[i]);
		free((*ast)->args);
	}
	free(*ast);
	*ast = NULL;
}

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
	return (ast);
}

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

void	expand_ast(t_ast_node **ast, t_token *tok, t_enum_type limit, char c)
{
	t_ast_node	*node;

	node = NULL;
	node = parsing_token(tok, limit);
	if (!node)
		return ;//free exit
	add_node(ast, node, c);
}

t_ast_node	*parsing_token(t_token *tok, t_enum_type limit)
{
	t_ast_node	*ast;
	t_token		*tmp;

	tmp = tok;
	ast = NULL;
	if (!tok || tok->type == limit)
		return (NULL);
	ast = check_pipe(tok, limit);
	if (ast)
		return (ast);
	while (tmp && tmp->next && tmp->next->type != limit)
	{
		if (tmp->type != TOKEN_STR && tmp->type != TOKEN_ENV_VAR)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL || tmp->type == TOKEN_STR || tmp->type == TOKEN_ENV_VAR)
		ast = parse_str(tok, limit);
	else if (tmp->type == TOKEN_REDIR_OUT || tmp->type == TOKEN_REDIR_APPEND
		|| tmp->type == TOKEN_REDIR_HEREDOC || tmp->type == TOKEN_REDIR_IN)
		ast = parse_redir_out(*tmp, tok);
	return (ast);
}
