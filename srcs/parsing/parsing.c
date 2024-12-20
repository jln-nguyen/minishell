/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/20 15:53:15 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tok(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
		return (-1);
	while (tok->next != NULL)
	{
		if (tok->type != TOKEN_STR && tok->type != TOKEN_ENV_VAR
			&& tok->type != TOKEN_PIPE)
		{
			if (tok->next->type != TOKEN_STR
				&& tok->next->type != TOKEN_ENV_VAR)
				return (-1);
		}
		tok = tok->next;
	}
	if (tok->type != TOKEN_STR && tok->type != TOKEN_ENV_VAR)
	{
		if (tok->next == NULL)
			return (-1);
	}
	return (0);
}

t_ast_node	*ft_parsing(char *cmd, t_env *env)
{
	t_ast_node	*ast;
	t_token		*tok;

	ast = NULL;
	tok = NULL;
	if (check_syntax(cmd) != 0)
		return (free(cmd), NULL);
	tok = ft_token(cmd, env);
	if (!tok)
		return (free(cmd), NULL);
	// if (check_tok(tok) == -1)
	// {
	// 	ft_putstr_fd("Syntax error\n", STDERR_FILENO);
	// 	return (free(cmd), ft_free(&tok), NULL);
	// }	
	// print_token(tok); //a supp
	free(cmd);
	ast = parsing_token(tok, -1);
	if (!ast)
		return (ft_free(&tok), NULL);
	generate_ast_diagram(ast); // a supp
	ft_free(&tok);
	return (ast);
}
