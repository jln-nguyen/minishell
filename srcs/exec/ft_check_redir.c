/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:19:48 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/03 18:08:54 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	new_cmd[i] = 0;
	return (free(cmd), new_cmd);
}

static int	ft_redir_out(t_ast_node *ast, t_env **env)
{
	int		file = 0;
	int		old_fd;
	t_ast_node	*tmp;

	tmp = ast;
	if (ast->right->type != TOKEN_STR)
	{
		while (tmp->right->right)
		{
			tmp = tmp->right;
			if (tmp->type == TOKEN_REDIR_OUT)
				file = open(tmp->left->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
			else if (tmp->type == TOKEN_REDIR_APPEND)
				file = open(tmp->left->args[0], O_CREAT | O_RDWR | O_APPEND, 0644);
			if (tmp->left->args[1])
				ast->left->args = save_cmd(ast->left->args, &tmp->left->args[1]);
		}
	}
	if (tmp->type == TOKEN_REDIR_OUT)
		file = open(tmp->right->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (tmp->type == TOKEN_REDIR_APPEND)
		file = open(tmp->right->args[0], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (file < 0)
		return (-1); //protect error
	if (tmp->right->args[1])
		ast->left->args = save_cmd(ast->left->args, &tmp->right->args[1]);
	old_fd = dup(STDOUT_FILENO);
	if (dup2(file, STDOUT_FILENO) == -1)
		return (close(file), -1); //return protect
	close(file);
	exec_cmd(ast->left, env);
	if (dup2(old_fd, STDOUT_FILENO) == -1)
		return (close(old_fd), -1); //return protect
	close(old_fd);
	return (0);
}

static int	ft_redir_in(t_ast_node *ast, t_env **env)
{
	int		file;
	int		old_fd;

	file = 0;
	if (ast->type == TOKEN_REDIR_IN)
		file = open(ast->right->args[0], O_RDONLY);
	else
		printf("gerer heredoc\n");
	if (file < 0)
		return (ft_printf(STDERR_FILENO, "Minishell: %s : No such file or directory\n", ast->right->args[0]), -1); //protect error
	old_fd = dup(STDIN_FILENO);
	if (dup2(file, STDIN_FILENO) == -1)
		return (close(file), -1); //return protect
	close(file);
	exec_cmd(ast->left, env);
	if (dup2(old_fd, STDIN_FILENO) == -1)
		return (close(old_fd), -1); //return protect
	close(old_fd);
	return (0);
}

void	ft_check_redir(t_ast_node *ast, t_env **env)
{
	if (ast->type == TOKEN_REDIR_APPEND || ast->type == TOKEN_REDIR_OUT)
		ft_redir_out(ast, env);
	else
		ft_redir_in(ast, env);
}
