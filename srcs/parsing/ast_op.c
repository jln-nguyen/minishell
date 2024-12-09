/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:04:00 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/04 13:11:12 by junguyen         ###   ########.fr       */
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

t_ast_node	*fill_arg(t_ast_node *ast, t_ast_node *new)
{
	int	i;

	i = 1;
	while (ast->right->args[i])
	{
		new->args[i - 1] = ft_strdup(ast->right->args[i]);
		if (!new->args[i - 1])
		{
			while (i > 0)
				free(new->args[--i]);
			free(new->args);
			new->args = NULL;
			return (NULL); // exit_fin
		}
		i++;
	}
	new->args[i - 1] = 0;
	return (new);
}

t_ast_node	*check_command(t_ast_node *ast)
{
	int			i;
	t_ast_node	*new;

	i = 1;
	if (!ast->right->args[i])
		return (ast);
	new = new_node(TOKEN_STR);
	if (!new)
		return (NULL); //exit fin
	while (ast->right->args[i])
		i++;
	new->args = malloc(sizeof(char *) * (i + 1));
	if (!new->args)
		return (free(new), NULL);
	new = fill_arg(ast, new);
	if (!new)
		return (ft_free_ast(&ast), NULL);
	while (i > 0)
	{
		free(ast->right->args[i]);
		i--;
	}
	ast->right->args[1] = 0;
	add_node(&ast, new, 'L');
	return (ast);
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
	// if (!ast->left)
	// 	ast = check_command(ast);
	return (ast);
}
