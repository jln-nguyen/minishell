/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_supp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:53:16 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/06 17:47:10 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_ast(t_ast_node *ast)
{
	char	*type[7] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND",
		"HERE_DOC", "ENV"};
	char	*tmp;

	tmp = NULL;
	if (!ast)
		return ;
	printf("-------AST-------\n");
	while (ast != NULL)
	{
		tmp = ft_strdup(type[ast->type]);
		printf("value : %s | type : %s\n", ast->args, tmp);
		free(tmp);
		ast = ast->right;
	}
}

void	print_token(t_token *tok)
{
	char	*type[7] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND",
		"HERE_DOC", "ENV"};
	char	*tmp;

	tmp = NULL;
	if (!tok)
		return ;
	printf("-------TOKEN-------\n");
	while (tok != NULL)
	{
		tmp = ft_strdup(type[tok->type]);
		printf("value : %s | type : %s\n", tok->value, tmp);
		free(tmp);
		tok = tok->next;
	}
}
