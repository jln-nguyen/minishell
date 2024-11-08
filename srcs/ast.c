/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:30:58 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/08 15:37:29 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free_ast(t_ast_node **ast)
{
	t_ast_node	*tmp;
	int			i;

	tmp = NULL;
	i = 0;
	while (*ast != NULL)
	{
		tmp = (*ast)->right;
		while ((*ast)->args[i])
			i++;
		while (i-- > 0)
			free((*ast)->args[i]);
		free((*ast)->args);
		free(*ast);
		*ast = tmp;
	}
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

void	add_left(t_ast_node **lst, t_ast_node *new)
{
	t_ast_node	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->left != NULL)
			tmp = tmp->left;
		tmp->left = new;
	}
}

void	expand_ast_left(t_ast_node **ast, t_token *tok)
{
	t_ast_node	*node;

	node = NULL;
	node = parsing_token(tok, ft_strlen_tok(tok, TOKEN_PIPE));
	if (!node)
	{
		printf("NULL\n");
		return ;
	}
	printf("%s\n", node->args[0]);
	printf("%s\n", node->args[1]);
	// printf("%s\n", node->args[2]);
	add_left(ast, node);
}

t_ast_node	*parse_pipe(t_token pipe, t_token *tok)
{
	t_ast_node	*ast;

	ast = NULL;
	ast = new_node(pipe.type);
	if (!ast)
		return (NULL);
	ast->args = malloc(sizeof(char *) * 2);
	if (!ast->args)
		return (NULL);
	ast->args[0] = ft_strdup(pipe.value);
	if (!ast->args[0])
		return (free(ast->args), NULL);
	printf("%s\n", ast->args[0]);
	ast->args[1] = 0;
	printf("%s\n", ast->args[1]);
	printf("%s\n", ast->args[2]);
	expand_ast_left(&ast, tok);
	return (ast);
}

void	add_right(t_ast_node **lst, t_token tok)
{
	t_ast_node	*tmp;
	t_ast_node	*new;

	new = NULL;
	new = new_node(tok.type);
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

int	ft_strlen_tok(t_token *tok, t_enum_type limit)
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

void	ft_fill_args(t_ast_node **head, t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		(*head)->args[i] = ft_strdup(tok->value);
		if (!(*head)->args[i])
		{
			while (i > 0)
				free((*head)->args[--i]);
			free((*head)->args);
			(*head)->args = NULL;
			return ;
		}
		i++;
		tok = tok->next;
	}
	(*head)->args[i] = 0;
}

t_ast_node	*parse_str(t_token *tok)
{
	t_ast_node	*head;
	int			len;

	len = ft_strlen_tok(tok, -1);
	head = NULL;
	head = new_node(tok->type);
	if (!head)
		return (NULL);
	head->args = malloc(sizeof(char *) * (len + 1));
	if (!head->args)
		return (NULL);
	ft_fill_args(&head, tok);
	if (!head->args)
		return (NULL);
	return (head);
}

t_ast_node	*parsing_token(t_token *tok, int len)
{
	t_ast_node	*ast;
	t_token		*tmp;

	tmp = tok;
	ast = NULL;
	if (!tok || len <= 0)
		return (NULL);
	while (tmp != NULL && len - 1 > 0)
	{
		if (tmp->type != TOKEN_STR && tmp->type != TOKEN_ENV_VAR)
			break ;
		tmp = tmp->next;
		len--;
	}
	if (tmp == NULL || tmp->type == TOKEN_STR || tmp->type == TOKEN_ENV_VAR)
		ast = parse_str(tok);
	else if (tmp->type == TOKEN_PIPE)
		ast = parse_pipe(*tmp, tok);
	else if (tmp->type == TOKEN_REDIR_HEREDOC)
		// ast = parse_heredoc();
		printf("tqt\n");
	else if (tmp->type == TOKEN_REDIR_APPEND)
		// ast = parse_append();
		printf("tqt\n");
	else if (tmp->type == TOKEN_REDIR_IN)
		// ast = parse_redir_in();
		printf("tqt\n");
	else if (tmp->type == TOKEN_REDIR_OUT)
		// ast = parse_redir_out();
		printf("tqt\n");
	return (ast);
}
