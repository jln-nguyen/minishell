/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/03 11:04:50 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	ctrl_d(t_data *data)
{
	printf("exit\n");
	ft_free_env(&data->env);
	if (g_signal != 0)
		exit(g_signal);
	rl_clear_history();
	exit(data->exit_code);
}

void	begin_program(t_data *data, char *tmp)
{
	data->ast = ft_parsing(tmp, data);
	if (data->ast)
	{
		ft_check_heredoc(&data->ast, data);
		ft_free_ast(&data->ast);
	}
}

void	prompt(t_data *data)
{
	char		*tmp;
	char		*gwd;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		g_signal = 0;
		gwd = get_prompt(data);
		tmp = readline(gwd);
		free(gwd);
		if (!tmp)
			ctrl_d(data);
		if (g_signal == 130)
		{
			data->exit_code = 130;
			g_signal = 0;
		}
		if (tmp[0] == '\0')
			continue ;
		add_history(tmp);
		begin_program(data, tmp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	data.env = NULL;
	data.ast = NULL;
	data.exit_code = 0;
	data.fd_in = 0;
	data.fd_out = 0;
	data.old_fd_in = 0;
	data.old_fd_out = 0;
	if (ac != 1)
		return (-2);
	(void)av;
	if (!envp || !*envp)
		ft_create_env(&data);
	else
		ft_getenv(&data, envp);
	if (!data.env)
		error_malloc_tok(NULL, &data);
	prompt(&data);
	ft_free_env(&data.env);
	return (0);
}
