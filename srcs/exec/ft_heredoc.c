/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:31:34 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/14 15:12:09 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sig(int signal)
{
	(void)signal;
	g_signal = 130;
	close(STDIN_FILENO);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	ft_read(char *end, t_data *data, int fd)
{
	char		*line;
	int			i;
	int			old_stdin;

	old_stdin = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (g_signal == 130)
		{
			dup2(old_stdin, STDIN_FILENO);
			close(old_stdin);
			break ;
		}
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
		i = 0;
		while (line[i])
		{
			if (line[i] == '$')
				line = change_str(line, i + 1, data);
			if (line[i] == '\0')
				break ;
			else
				i++;
		}
		if (!line)
			return ; // protect
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(old_stdin);
}

int	ft_heredoc(t_ast_node *ast, t_data *data, int i)
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
	ft_read(ast->args[0], data, fd);
	if (g_signal == 130)
	{
		unlink(file);
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

void	check_heredoc(t_ast_node **ast, t_data *data)
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
			check_heredoc(&(tmp)->left, data);
			if (tmp->fd_heredoc < 0)
				return (ft_putstr_fd("errorbbb\n", STDERR_FILENO), (void)-1); //?
		}
		else if (tmp->type == TOKEN_REDIR_HEREDOC)
		{
			if (tmp->right->type == TOKEN_STR)
			{
				tmp->fd_heredoc = ft_heredoc(tmp->right, data, i);
				if (g_signal == 130)
					return ;
			}
			else
			{
				tmp->fd_heredoc = ft_heredoc(tmp->right->left, data, i);
				if (g_signal == 130)
					return ;
			}
			i++;
			if (tmp->fd_heredoc < 0)
				return (ft_putstr_fd("erroraaa\n", STDERR_FILENO), (void)-1); //?
		}
		tmp = tmp->right;
	}
}
