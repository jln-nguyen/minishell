/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/08 12:23:37 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	sigint_process(int signal)
{
	if (signal == SIGQUIT)
	{
		g_exit_status = 131;
		printf("Quit (core dumped)");
	}
	else
		g_exit_status = 130;
	printf("\n");
}

void	sigint_handler(int signal)
{
	(void)signal;
	g_exit_status = 130;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int signal)
{
	(void)signal;
	g_exit_status = 131;
	printf("Quit (core dumped)\n");
	rl_on_new_line();
	rl_redisplay();
}

char	*color_gwd(char *gwd, t_env *env)
{
	char	*tmp;
	char	*home;

	if (!gwd)
		return (NULL);
	tmp = ft_strdup("HOME");
	home = change_value(tmp, env);
	if (ft_strncmp(home, gwd, ft_strlen(home)) == 0)
	{
		tmp = ft_substr(gwd, ft_strlen(home), ft_strlen(gwd));
		free(home);
		free(gwd);
		gwd = ft_strjoin("~", tmp);
		free(tmp);
	}
	tmp = ft_strbigjoin("\001\033[0;36m\033[1m\002", gwd, "\001\033[0m\002");
	free(gwd);
	return (tmp);
}

void	prompt(t_env **env)
{
	char		*tmp;
	char		*gwd;
	t_ast_node	*ast;

	ast = NULL;
	while (1)
	{
		tmp = getcwd(NULL, 0);
		gwd = ft_strjoin(tmp, "$ ");
		gwd = color_gwd(gwd, *env);
		free(tmp);
		if (!gwd)
			return ((void)ft_printf(STDERR_FILENO, ("Malloc error\n")));
		tmp = readline(gwd);
		if (!tmp)
			return (printf("exit\n"), free(gwd));
		add_history(tmp);
		free(gwd);
		ast = ft_parsing(tmp, *env);
		if (ast)
		{
			ft_check_heredoc(&ast, env);
			ft_free_ast(&ast);
		}
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env		*env;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!envp || !*envp)
		env = ft_create_env();
	else
		env = ft_getenv(envp);
	if (!env)
		return (-1);
	prompt(&env);
	ft_free_env(&env);
	return (0);
}
