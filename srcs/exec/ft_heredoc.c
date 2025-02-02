/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:31:34 by bvictoir          #+#    #+#             */
/*   Updated: 2025/02/02 13:13:13 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sig(int signal)
{
	(void)signal;
	g_signal = 130;
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
	rl_on_new_line();
	rl_done = 1;
}

static int	event(void)
{
	return (0);
}

void	ft_read(char *end, t_data *data, int fd)
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
				line = change_str(line, i + 1, data, NULL); // changez fonction
		else if (line[i] == '\0') // je laisse le else if au lieu de if ??
			break ;
		else
			i++;
		if (!line)
			return ; // normalement pas besoin car change_str gere les erreurs
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
		return (-1);
	ft_read(ast->args[0], data, fd);
	if (g_signal == 130)
		return (unlink(file), close(fd), free(file), -1);
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
				return (ft_putstr_fd("error\n", STDERR_FILENO), (void)-1); //?
		}
		else if (tmp->type == TOKEN_REDIR_HEREDOC)
		{
			if (redic_heredoc(tmp, data, &i))
				return ;
			i++;
		}
		tmp = tmp->right;
	}
}
