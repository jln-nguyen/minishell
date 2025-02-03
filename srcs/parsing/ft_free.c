/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:02:46 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/29 13:45:16 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab_var_env(char ***tab)
{
	free((*tab)[0]);
	free((*tab)[1]);
	free((*tab)[2]);
	free((*tab)[3]);
	free(*tab);
	*tab = NULL;
}

void	error_malloc_tok(t_token **tok, t_data *data)
{
	if (tok)
		ft_free(tok);
	if (data->env)
		ft_free_env(&data->env);
	ft_printf(STDERR_FILENO, "Minishell: Malloc error\n");
	exit(EXIT_FAILURE);
}

void	ft_free_ast(t_ast_node **ast)
{
	int	i;

	i = 0;
	if (!ast || !*ast)
		return ;
	ft_free_ast(&(*ast)->left);
	ft_free_ast(&(*ast)->right);
	if ((*ast)->args)
	{
		while ((*ast)->args[i])
			free((*ast)->args[i++]);
		free((*ast)->args);
	}
	if ((*ast)->fd_heredoc > 0)
		close((*ast)->fd_heredoc);
	free(*ast);
	*ast = NULL;
}
