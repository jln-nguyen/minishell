/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_supp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:53:16 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/26 17:16:50 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	print_ast(t_ast_node *ast)
{
	char	*type[7] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND",
		"HERE_DOC", "ENV"};
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (!ast)
		return ;
	printf("-------AST-------\n");
	while (ast != NULL)
	{
		tmp = ft_strdup(type[ast->type]);
		printf("value : ");
		while (ast->args[i])
		{
			printf("%s ", ast->args[i]);
			i++;
		}
		printf("| type : %s\n", tmp);
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
