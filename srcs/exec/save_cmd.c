/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:17:11 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/29 18:09:14 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_left_node(t_ast_node **ast, t_data *data)
{
	t_ast_node	*node;

	node = new_node(TOKEN_STR);
	if (!node)
		ft_err(data, "Malloc");
	node->args = malloc(sizeof(char *) * 1);
	if (!node->args)
		(free(node), ft_err(data, "Malloc"));
	node->args[0] = 0;
	add_node(ast, node, 'L');
}

static void	ft_fill_cmd(char **cmd, char **new_cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		new_cmd[i] = ft_strdup(cmd[i]);
		if (!new_cmd[i])
		{
			ft_free_tab(&new_cmd);
			ft_err(data, "Malloc");
		}
		i++;
	}
}

static char	**save_cmd(char **cmd, char **arg, t_data *data)
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
		(ft_err(data, "Malloc"), ft_free_tab(&cmd));
	new_cmd[i + j] = 0;
	ft_fill_cmd(cmd, new_cmd, data);
	ft_fill_cmd(arg, &new_cmd[i], data);
	if (cmd[0] == 0)
		free(cmd);
	else
		ft_free_tab(&cmd);
	return (new_cmd);
}

void	search_cmd(t_ast_node **ast, t_data *data)
{
	t_ast_node	*tmp;

	tmp = *ast;
	if (!tmp->left)
		create_left_node(ast, data);
	while (tmp->right->right)
	{
		tmp = tmp->right;
		if (tmp->left->args[1])
			(*ast)->left->args = save_cmd((*ast)->left->args,
					&tmp->left->args[1], data);
	}
	if (tmp->right->args[1])
		(*ast)->left->args = save_cmd((*ast)->left->args, &tmp->right->args[1],
				data);
}
