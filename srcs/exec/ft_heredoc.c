/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:31:34 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/08 15:06:38 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sig(int signal)
{
	(void)signal;
	// close(STDIN_FILENO);
	g_exit_status = -1;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	ft_read(char *end, t_env **env, int fd)
{
	char		*line;
	int			i;

	while (1)
	{
		line = readline("> ");
		if (g_exit_status == -1)
			break ;
		if (!line)
		{
			ft_printf(STDERR_FILENO, "Minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", end);
			break ;
		}
		if (!ft_strcmp(line, end))
		{
			free(line);
			break ;
		}
		i = -1;
		while (line[++i])
			if (line[i] == '$')
				line = change_str(line, i + 1, *env);
		if (!line)
			return ; // protect
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

int	ft_heredoc(t_ast_node *ast, t_env **env, int i)
{
	int		fd;
	char	*file;
	char	*nb_file;

	nb_file = ft_itoa(i);
	file = ft_strjoin(".heredoc", nb_file);
	free(nb_file);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	ft_read(ast->args[0], env, fd);
	if (g_exit_status == -1)
	{
		close(fd);
		free(file);
		return (-1);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	unlink(file);
	free(file);
	return (fd);
}

void	check_heredoc(t_ast_node **ast, t_env **env)
{
	t_ast_node	*tmp;
	int			i;

	i = 0;
	tmp = *ast;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sig);
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			check_heredoc(&(tmp)->left, env);
			if (tmp->fd_heredoc < 0)
				return (ft_putstr_fd("errorbbb\n", STDERR_FILENO), (void)-1); //?
		}
		else if (tmp->type == TOKEN_REDIR_HEREDOC)
		{
			if (tmp->right->type == TOKEN_STR)
			{
				tmp->fd_heredoc = ft_heredoc(tmp->right, env, i);
				if (g_exit_status == -1)
				{
					// sigint_handler(SIGINT);
					return ;
				}
			}
			else
			{
				tmp->fd_heredoc = ft_heredoc(tmp->right->left, env, i);
				if (g_exit_status == -1)
				{
					// sigint_handler(SIGINT);
					return ;
				}
			}
			i++;
			if (tmp->fd_heredoc < 0)
				return (ft_putstr_fd("erroraaa\n", STDERR_FILENO), (void)-1); //?
		}
		tmp = tmp->right;
	}
}

// void	check_heredoc(t_ast_node **ast, t_env **env)
// {
// 	int	pid;

// 	pid = fork();
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	if (pid == -1)
// 		return ;
// 	if (pid == 0)
// 		check_heredoc2(ast, env);
// 	else
// 		wait(&pid);
// 	return ;
// }
