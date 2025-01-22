/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:37:57 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/22 14:40:41 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data, t_ast_node **ast)
{
	char	**tab;
	// int		status;
	tab = NULL;
	if (!*ast || !ast)
		return ;
	if ((*ast)->type != TOKEN_STR)
		ft_redir(data, ast);
	else if (!*(*ast)->args || !(*ast)->args[0])
		return ;
	else
	{
		data->exit_code = ft_check_builtins(data, (*ast), &data->env);
		if (data->exit_code == -1)
		{
			tab = struc_to_char(data->env);
			if (!tab || !*tab)
				return ; //protect
			data->exit_code = ft_execve(tab, ast, data);
			ft_free_tab(&tab);
		}
	}
}
