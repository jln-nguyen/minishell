/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:17:11 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/22 14:41:49 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_left_node(t_ast_node **ast)
{
	t_ast_node	*node;

	node = new_node(TOKEN_STR);
	if (!node)
		return ; //protect malloc
	node->args = malloc(sizeof(char *) * 1);
	if (!node->args)
		return ; //protect malloc
	node->args[0] = 0;
	add_node(ast, node, 'L');
}

static void	ft_fill_cmd(char **cmd, char **new_cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		new_cmd[i] = ft_strdup(cmd[i]);
		if (!new_cmd[i])
		{
			ft_free_tab(&new_cmd);
			return ;
		}
		i++;
	}
}

static char	**save_cmd(char **cmd, char **arg)
{
	char	**new_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_cmd = NULL;
	while (cmd[i])
		i++;
	while (arg[j])
		j++;
	new_cmd = malloc(sizeof(char *) * (i + j + 1));
	if (!new_cmd)
		return (NULL);
	new_cmd[i + j] = 0;
	ft_fill_cmd(cmd, new_cmd);
	ft_fill_cmd(arg, &new_cmd[i]);
	if (cmd[0] == 0)
		free(cmd);
	else
		ft_free_tab(&cmd);
	return (new_cmd);
}

void	search_cmd(t_ast_node **ast)
{
	t_ast_node	*tmp;

	tmp = *ast;
	if (!tmp->left)
		create_left_node(ast);
	while (tmp->right->right)
	{
		tmp = tmp->right;
		if (tmp->left->args[1])
			(*ast)->left->args = save_cmd((*ast)->left->args,
					&tmp->left->args[1]);
	}
	if (tmp->right->args[1])
		(*ast)->left->args = save_cmd((*ast)->left->args, &tmp->right->args[1]);
}
