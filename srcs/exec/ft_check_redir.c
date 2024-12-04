/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:19:48 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/04 18:05:36 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_left_node(t_ast_node **ast)
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

char	**save_cmd(char **cmd, char **arg)
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
	i = 0;
	j = 0;
	while (cmd[i])
	{
		new_cmd[i] = ft_strdup(cmd[i]);
		if (!new_cmd[i])
		{
			ft_free_tab(&new_cmd);
			return (NULL);
		}
		i++;
	}
	while (arg[j])
	{
		new_cmd[i] = ft_strdup(arg[j]);
		if (!new_cmd[i])
		{
			ft_free_tab(&new_cmd);
			return (NULL);
		}
		i++;
		j++;
	}
	while (j > 0)
	{
		free(arg[j]);
		j--;
	}
	arg[1] = 0;
	new_cmd[i] = 0;
	return (free(cmd), new_cmd);
}

// static int	ft_redir_out(t_ast_node *ast, t_env **env)
// {
// 	int		file = 0;
// 	int		old_fd;
// 	t_ast_node	*tmp;

// 	tmp = ast;
// 	if (!ast->left)
// 		create_left_node(&ast);
// 	if (ast->right->type != TOKEN_STR)
// 	{
// 		while (tmp->right->right)
// 		{
// 			tmp = tmp->right;
// 			if (tmp->type == TOKEN_REDIR_OUT)
// 				file = open(tmp->left->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 			else if (tmp->type == TOKEN_REDIR_APPEND)
// 				file = open(tmp->left->args[0], O_CREAT | O_RDWR | O_APPEND, 0644);
// 			if (tmp->left->args[1])
// 				ast->left->args = save_cmd(ast->left->args, &tmp->left->args[1]);
// 		}
// 	}
// 	if (tmp->type == TOKEN_REDIR_OUT)
// 		file = open(tmp->right->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	else if (tmp->type == TOKEN_REDIR_APPEND)
// 		file = open(tmp->right->args[0], O_CREAT | O_RDWR | O_APPEND, 0644);
// 	if (file < 0)
// 		return (-1); //protect error
// 	if (tmp->right->args[1])
// 		ast->left->args = save_cmd(ast->left->args, &tmp->right->args[1]);
// 	old_fd = dup(STDOUT_FILENO);
// 	if (dup2(file, STDOUT_FILENO) == -1)
// 		return (close(file), -1); //return protect
// 	close(file);
// 	exec_cmd(ast->left, env);
// 	if (dup2(old_fd, STDOUT_FILENO) == -1)
// 		return (close(old_fd), -1); //return protect
// 	close(old_fd);
// 	return (0);
// }

// static int	ft_redir_in(t_ast_node *ast, t_env **env)
// {
// 	int		file = 0;
// 	int		old_fd;
// 	t_ast_node	*tmp;

// 	tmp = ast;
// 	if (!ast->left)
// 		create_left_node(&ast);
// 	if (ast->right->type != TOKEN_STR)
// 	{
// 		while (tmp->right->right)
// 		{
// 			tmp = tmp->right;
// 			if (tmp->type == TOKEN_REDIR_IN)
// 				file = open(tmp->left->args[0], O_RDONLY);
// 			else if (tmp->type == TOKEN_REDIR_HEREDOC)
// 				printf("gerer heredoc\n");
// 			else
// 				ft_redir_out(tmp, env);
// 			if (tmp->left->args[1])
// 				ast->left->args = save_cmd(ast->left->args, &tmp->left->args[1]);
// 		}
// 	}
// 	if (tmp->type == TOKEN_REDIR_IN)
// 		file = open(tmp->right->args[0], O_RDONLY);
// 	else
// 		printf("gerer heredoc\n");
// 	if (file < 0)
// 		return (ft_printf(STDERR_FILENO, "Minishell: %s : No such file or directory\n", tmp->right->args[0]), -1); //protect error
// 	if (tmp->right->args[1])
// 		ast->left->args = save_cmd(ast->left->args, &tmp->right->args[1]);
// 	old_fd = dup(STDIN_FILENO);
// 	if (dup2(file, STDIN_FILENO) == -1)
// 		return (close(file), -1); //return protect
// 	close(file);
// 	exec_cmd(ast->left, env);
// 	if (dup2(old_fd, STDIN_FILENO) == -1)
// 		return (close(old_fd), -1); //return protect
// 	close(old_fd);
// 	return (0);
// }

static int	ft_redir_out(t_ast_node *ast)
{
	int	file = 0;
	t_ast_node	*tmp;

	tmp = ast;
	if (ast->right->type != TOKEN_STR)
	{
		while (tmp->right->right)
		{
			if (tmp->right->type == TOKEN_REDIR_OUT || (tmp->type == TOKEN_REDIR_OUT && (tmp->right->type == TOKEN_REDIR_IN || tmp->right->type == TOKEN_REDIR_HEREDOC)))
			{
				if (file)
					close(file);
				file = open(tmp->left->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
			}
			else if (tmp->type == TOKEN_REDIR_APPEND || (tmp->type == TOKEN_REDIR_APPEND && (tmp->right->type == TOKEN_REDIR_IN || tmp->right->type == TOKEN_REDIR_HEREDOC)))
			{
				if (file)
					close(file);
				file = open(tmp->left->args[0], O_CREAT | O_RDWR | O_APPEND, 0644);
			}
			tmp = tmp->right;
		}
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
		return (ft_printf(STDERR_FILENO, "Minishell: %s : No such file or directory\n", tmp->right->args[0]), -1); //protect error
	return (file);
}

static int	ft_redir_in(t_ast_node *ast)
{
	int		file = 0;
	t_ast_node	*tmp;

	tmp = ast;
	if (ast->right->type != TOKEN_STR)
	{
		while (tmp->right->right)
		{
			if (tmp->right->type == TOKEN_REDIR_IN || (tmp->type == TOKEN_REDIR_IN && (tmp->right->type == TOKEN_REDIR_OUT || tmp->right->type == TOKEN_REDIR_APPEND)))
			{
				if (file)
					close(file);
				file = open(tmp->left->args[0], O_RDONLY);
			}
			else if (tmp->right->type == TOKEN_REDIR_HEREDOC || (tmp->type == TOKEN_REDIR_HEREDOC && (tmp->right->type == TOKEN_REDIR_OUT || tmp->right->type == TOKEN_REDIR_APPEND)))
				printf("gerer heredoc\n");
			tmp = tmp->right;
		}
	}
	if (tmp->type == TOKEN_REDIR_IN)
	{
		if (file)
			close(file);
		file = open(tmp->right->args[0], O_RDONLY);
	}
	else if (tmp->type == TOKEN_REDIR_HEREDOC)
		printf("gerer heredoc\n");
	if (file < 0)
		return (ft_printf(STDERR_FILENO, "Minishell: %s : No such file or directory\n", tmp->right->args[0]), -1); //protect error
	return (file);
}

t_ast_node	*search_cmd(t_ast_node *ast)
{
	t_ast_node	*tmp;

	tmp = ast;
	if (!tmp->left)
		create_left_node(&ast);
	while (tmp->right->right)
	{
		tmp = tmp->right;
		if (tmp->left->args[1])
			ast->left->args = save_cmd(ast->left->args, &tmp->left->args[1]);
	}
	if (tmp->right->args[1])
		ast->left->args = save_cmd(ast->left->args, &tmp->right->args[1]);
	return (ast);
}

void	ft_check_redir(t_ast_node *ast, t_env **env)
{
	int	old_fd_in = 1;
	int	old_fd_out=0;
	int	file_in=0;
	int	file_out=0;

	ast = search_cmd(ast);
	// if (ast->type == TOKEN_REDIR_APPEND || ast->type == TOKEN_REDIR_OUT)
	// 	ft_redir_out(ast, env);
	// else
	// 	ft_redir_in(ast, env);
	file_in = ft_redir_in(ast);
	if (file_in > 0)
	{
		old_fd_in = dup(STDIN_FILENO);
		if (dup2(file_in, STDIN_FILENO) == -1)
			return ((void)close(file_in)); //return protect
		close(file_in);
	}
	file_out = ft_redir_out(ast);
	if (file_out > 0)
	{
		old_fd_out = dup(STDOUT_FILENO);
		if (dup2(file_out, STDOUT_FILENO) == -1)
			return ((void)close(file_out)); //return protect
		close(file_out);
	}
	exec_cmd(ast->left, env);
	if (old_fd_in != 0)
	{
		if (dup2(old_fd_in, STDIN_FILENO) == -1)
			return ((void)close(old_fd_in)); //return protect
		close(old_fd_in);
	}
	if (old_fd_out != 1)
	{
		if (dup2(old_fd_out, STDOUT_FILENO) == -1)
			return ((void)close(old_fd_out)); //return protect
		close(old_fd_out);
	}
}
