/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:19:48 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/02 18:25:45 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redir_out(t_ast_node *ast, t_env **env)
{
	int		file = 0;
	int		old_fd;
	char	**tab;

	tab = NULL;
		// return (printf("gerer si plusieurs redir\n")) ;
	if (ast->type == TOKEN_REDIR_OUT && ast->right->type == TOKEN_STR)
		file = open(ast->right->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (ast->type == TOKEN_REDIR_APPEND && ast->right->type == TOKEN_STR)
		file = open(ast->right->args[0], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (file < 0)
		return (-1); //protect error
	old_fd = dup(STDOUT_FILENO);
	if (dup2(file, STDOUT_FILENO) == -1)
		return (close(file), -1); //return protect
	close(file);
	exec_cmd(ast->left, env);
	if (ast->right->type != TOKEN_STR)
		exec_cmd(ast->right, env);
	if (dup2(old_fd, STDOUT_FILENO) == -1)
		return (close(old_fd), -1); //return protect
	close(old_fd);
	return (0);
}

static int	ft_redir_in(t_ast_node *ast, t_env **env)
{
	int		file;
	int		old_fd;
	char	**tab;

	tab = NULL;
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
	exec_cmd(&(*ast->left), env);
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
