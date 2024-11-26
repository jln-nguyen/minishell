/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/26 14:53:16 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_tok(t_token *tok)
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

int	ft_parsing(char *cmd, t_env *env)
{
	t_ast_node	*ast;
	t_token		*tok;

	if (check_syntax(cmd) != 0)
		return (free(cmd), -1);
	tok = ft_token(cmd);
	if (!tok)
		return (free(cmd), -2);
	if (check_tok(tok) == -1)
	{
		ft_putstr_fd("Syntax error\n", STDERR_FILENO);
		return (free(cmd), ft_free(&tok), -3);
	}	
	print_token(tok); //a supp
	free(cmd);
	ast = parsing_token(tok, -1);
	if (!ast)
		return (ft_free_env(&env), ft_free(&tok), -4);
	generate_ast_diagram(ast); // a supp
	ft_free(&tok);
	ft_free_ast(&ast);
	return (0);
}
