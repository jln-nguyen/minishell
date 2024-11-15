/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:30:58 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/13 12:13:22 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_ast(t_ast_node **ast)
{
	// t_ast_node	*tmp;
	int			i;

	// tmp = NULL;
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
		return ; //free exit
	add_node(ast, node, c);
}

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

void	ft_fill_args(t_ast_node **head, t_token *tok, t_enum_type limit)
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
			return ;
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
		return (NULL);
	ft_fill_args(&head, tok, limit);
	if (!head->args)
		return (NULL);
	return (head);
}

t_ast_node	*parsing_token(t_token *tok, t_enum_type limit)
{
	t_ast_node	*ast;
	t_token		*tmp;

	tmp = tok;
	ast = NULL;
	if (!tok)
		return (NULL);
	while (tmp && tmp->next && tmp->next->type != limit)
	{
		if (tmp->type != TOKEN_STR && tmp->type != TOKEN_ENV_VAR)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL || tmp->type == TOKEN_STR || tmp->type == TOKEN_ENV_VAR)
		ast = parse_str(tok, limit);
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
