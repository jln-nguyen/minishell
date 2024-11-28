/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/28 18:15:52 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char		*tmp;
	char		*gwd;
	t_ast_node	*ast;

	ast = NULL;
	tmp = NULL;
	gwd = NULL;
	while (1)
	{
		gwd = ft_strjoin(getcwd(NULL, 0), "$ ");
		if (!gwd)
			return ; // a proteger
		tmp = readline(gwd);
		if (!tmp)
			return (free(gwd)); // a proteger
		add_history(tmp);
		ast = ft_parsing(tmp);
		if (ast)
			ft_exec(ast, &env);
		free(gwd);
	}
	// (void)env;
	// tmp = get_next_line(0);
	// if (ft_parsing(tmp) != 0)
	// 	return ; //gnl a supp, pour mieux verif valgrind
	ft_free_ast(&ast);
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
	prompt(env);
	ft_free_env(&env);
	return (0);
}
