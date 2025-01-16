/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:21:25 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/16 10:14:19 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mult_redir_in(int file, t_ast_node **tmp, t_env **env)
{
	(void)env;
	while ((*tmp)->right->right)
	{
		if ((*tmp)->type == TOKEN_REDIR_IN)
		{
			if (file > 0)
				close(file);
			file = open((*tmp)->right->left->args[0], O_RDONLY);
		}
		else if ((*tmp)->type == TOKEN_REDIR_HEREDOC)
		{
			if (file > 0)
				close(file);
			file = (*tmp)->fd_heredoc;
		}
		if (file < 0)
			return (ft_printf(2, "Minishell: %s : No such file or directory\n",
					(*tmp)->right->left->args[0]), -1);
		*tmp = (*tmp)->right;
	}
	return (file);
}

int	ft_redir_in(t_ast_node *ast, t_env **env)
{
	int			file;
	t_ast_node	*tmp;

	file = 0;
	tmp = ast;
	if (ast->right->type != TOKEN_STR)
	{
		file = mult_redir_in(file, &tmp, env);
		if (file < 0)
			return (-1);
	}
	if (tmp->type == TOKEN_REDIR_IN)
	{
		if (file > 0)
			close(file);
		file = open(tmp->right->args[0], O_RDONLY);
	}
	else if (tmp->type == TOKEN_REDIR_HEREDOC)
	{
		if (file > 0)
			close(file);
		file = tmp->fd_heredoc;
	}
	if (file < 0)
		return (ft_printf(STDERR_FILENO, "Minishell: %s : %s\n",
				tmp->right->args[0], strerror(errno)), -1); // protect error
	return (file);
}

static int	mult_redir_out(int file, t_ast_node **tmp)
{
	while ((*tmp)->right->right)
	{
		if ((*tmp)->type == TOKEN_REDIR_OUT)
		{
			if (file > 0)
				close(file);
			file = open((*tmp)->right->left->args[0],
					O_CREAT | O_RDWR | O_TRUNC, 0644);
		}
		else if ((*tmp)->type == TOKEN_REDIR_APPEND)
		{
			if (file > 0)
				close(file);
			file = open((*tmp)->right->left->args[0],
					O_CREAT | O_RDWR | O_APPEND, 0644);
		}
		if (file < 0)
			return (ft_printf(STDERR_FILENO, "Minishell: %s : %s\n",
					(*tmp)->right->left->args[0], strerror(errno)), -1);
				// protect error
		*tmp = (*tmp)->right;
	}
	return (file);
}

int	ft_redir_out(t_ast_node *ast)
{
	int			file;
	t_ast_node	*tmp;

	file = 0;
	tmp = ast;
	if (ast->right->type != TOKEN_STR)
	{
		file = mult_redir_out(file, &tmp);
		if (file < 0)
			return (-1);
	}
	if (tmp->type == TOKEN_REDIR_OUT)
	{
		if (file)
			close(file);
		file = open(tmp->right->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (tmp->type == TOKEN_REDIR_APPEND)
	{
		if (file)
			close(file);
		file = open(tmp->right->args[0], O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	if (file < 0)
		return (ft_printf(STDERR_FILENO, "Minishell: %s : %s\n",
				tmp->right->args[0], strerror(errno)), -1); // protect error
	return (file);
}
