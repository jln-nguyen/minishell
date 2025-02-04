/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:31:34 by bvictoir          #+#    #+#             */
/*   Updated: 2025/02/04 16:36:25 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	event(void)
{
	return (0);
}

void	ft_read(char *end, t_data *data, int fd, char *file)
{
	char	*line;
	int		i;

	rl_event_hook = event;
	while (1)
	{
		line = readline("> ");
		if (g_signal == 130 || !ft_strcmp(line, end) || !line)
		{
			ft_break_here(line, end);
			break ;
		}
		i = 0;
		while (line[i])
			if (line[i] == '$')
				line = expand_heredoc(line, data, &i, file);
		else if (line[i] == '\0')
			break ;
		else
			i++;
		if (!line)
			return ;
		(ft_putstr_fd(line, fd), ft_putstr_fd("\n", fd), free(line));
	}
}

int	ft_heredoc(t_ast_node *ast, t_data *data, int i)
{
	int		fd;
	char	*file;
	char	*nb_file;

	nb_file = ft_itoa(i);
	if (!nb_file)
		ft_err(data, "Malloc");
	file = ft_strjoin(".heredoc", nb_file);
	if (!file)
		(free(nb_file), free(file), ft_err(data, "Malloc"));
	free(nb_file);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (free(file), -1);
	ft_read(ast->args[0], data, fd, file);
	if (g_signal == 130)
		return (unlink(file), close(fd), free(file), -1);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free(file), -1);
	unlink(file);
	free(file);
	return (fd);
}

static int	redic_heredoc(t_ast_node *tmp, t_data *data, int *i)
{
	if (tmp->right->type == TOKEN_STR)
		tmp->fd_heredoc = ft_heredoc(tmp->right, data, *i);
	else
		tmp->fd_heredoc = ft_heredoc(tmp->right->left, data, *i);
	if (g_signal == 130)
		return (1);
	if (tmp->fd_heredoc < 0)
		return (1);
	return (0);
}

int	check_heredoc(t_ast_node **ast, t_data *data)
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
			if (check_heredoc(&(tmp)->left, data) == 1)
				return (1);
		}
		else if (tmp->type == TOKEN_REDIR_HEREDOC)
		{
			if (redic_heredoc(tmp, data, &i) == 1)
				return (1);
			i++;
		}
		tmp = tmp->right;

	}
	return (0);
}
