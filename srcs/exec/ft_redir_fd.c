/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:21:25 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/11 15:08:42 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mult_redir_in(int file, t_ast_node **tmp, t_env **env)
{
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
			file = ft_heredoc((*tmp)->right->left, env);
		}
		if (file < 0)
			return (ft_printf(2, "Minishell: %s\n", strerror(errno)), -1);
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
		file = mult_redir_in(file, &tmp, env);
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
		file = ft_heredoc(tmp->right, env);
	}
	if (file < 0)
		return (ft_printf(STDERR_FILENO, "Minishell: %s : No such file or directory\n", tmp->right->args[0]), -1); //protect error
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
			file = open((*tmp)->right->left->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		}
		else if ((*tmp)->type == TOKEN_REDIR_APPEND)
		{
			if (file > 0)
				close(file);
			file = open((*tmp)->right->left->args[0], O_CREAT | O_RDWR | O_APPEND, 0644);
		}
		if (file < 0)
			return (ft_printf(STDERR_FILENO, "Minishell: %s : No such file or directory\n", (*tmp)->right->args[0]), -1); //protect error	
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
		file = mult_redir_out(file, &tmp);
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
		return (ft_printf(STDERR_FILENO, "Minishell: %s : No such file or directory\n", tmp->right->args[0]), -1); //protect error
	return (file);
}
