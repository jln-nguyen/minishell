/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/16 13:24:43 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	sigint_process(int signal)
{
	if (signal == SIGQUIT)
		printf("Quit (core dumped)\n");
	// printf("\n");
}

void	sigint_handler(int signal)
{
	(void)signal;
	g_signal = 130;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int signal)
{
	(void)signal;
	g_signal = 131;
	printf("Quit (core dumped)\n");
	rl_on_new_line();
	rl_redisplay();
}

char	*color_gwd(char *gwd, t_data *data)
{
	char	*tmp;
	char	*home;

	if (!gwd)
		return (NULL);
	tmp = ft_strdup("HOME");
	home = change_value(tmp, data);
	if (ft_strncmp(home, gwd, ft_strlen(home)) == 0)
	{
		tmp = ft_substr(gwd, ft_strlen(home), ft_strlen(gwd));
		free(gwd);
		gwd = ft_strjoin("~", tmp);
		free(tmp);
	}
	free(home);
	tmp = ft_strbigjoin("\001\033[0;36m\033[1m\002", gwd, "\001\033[0m\002");
	free(gwd);
	return (tmp);
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
		tmp = getcwd(NULL, 0);
		gwd = ft_strjoin(tmp, "$ ");
		gwd = color_gwd(gwd, data);
		free(tmp);
		if (!gwd)
			return ((void)ft_printf(STDERR_FILENO, ("Malloc error\n")));
		tmp = readline(gwd);
		free(gwd);
		if (!tmp)
		{
			printf("exit\n");
			ft_free_env(&data->env);
			if (g_signal != 0)
				exit(g_signal);
			exit(data->exit_code);
		}
		if (g_signal == 130)
		{
			data->exit_code = 130;
			g_signal = 0;
		}
		add_history(tmp);
		data->ast = ft_parsing(tmp, data);
		if (data->ast)
		{
			ft_check_heredoc(&data->ast, data);
			ft_free_ast(&data->ast);
		}
		// rl_clear_history();
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	data.env = NULL;
	data.ast = NULL;
	data.exit_code = 0;
	if (ac != 1)
		return (-2);
	(void)av;
	// signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, SIG_IGN);
	if (!envp || !*envp)
		ft_create_env(&data);
	else
		ft_getenv(&data, envp); //incrementer shlvl ?
	if (!data.env)
		return (-1);
	prompt(&data);
	ft_free_env(&data.env);
	return (0);
}
