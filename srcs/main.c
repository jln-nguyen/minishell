/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/27 18:07:39 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	prompt(t_env *env)
{
	char	*tmp;

	(void)env;
	tmp = NULL;
	while (1)
	{
		tmp = readline("Minishell> ");
		if (!tmp)
			return ;
		if (tmp)
			add_history(tmp);
		ft_parsing(tmp);
	}
	// tmp = get_next_line(0);
	// if (ft_parsing(tmp, env) != 0)
	// 	return ; //gnl a supp, pour mieux verif valgrind
}

int	main(int ac, char **av, char **envp)
{
	t_env		*env;

	(void)ac;
	(void)av;
	signal(SIGINT, &sigint_handler);
	if (!envp || !*envp)
		env = ft_create_env();
	else
		env = ft_getenv(envp);
	if (!env)
		return (-1);
	print_env(env);
	prompt(env);
	ft_free_env(&env);
	return (0);
}
