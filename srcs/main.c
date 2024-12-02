/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/02 17:19:06 by junguyen         ###   ########.fr       */
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

char	*color_gwd(char *gwd)
{
	char	*tmp;

	if (!gwd)
		return (NULL);
	tmp = ft_strbigjoin("\033[0;36m\033[1m", gwd, "\033[0m");
	free(gwd);
	return (tmp);
}

void	prompt(t_env *env)
{
	char		*tmp;
	char		*gwd;
	t_ast_node	*ast;

	while (1)
	{
		tmp = getcwd(NULL, 0);
		gwd = ft_strjoin(tmp, "\033[0;35m\033[1m$\033[0m ");
		gwd = color_gwd(gwd);
		free(tmp);
		if (!gwd)
			return ; // a proteger
		tmp = readline(gwd);
		if (!tmp)
			return (free(gwd)); // a proteger
		add_history(tmp);
		ast = ft_parsing(tmp);
		if (ast)
			ft_exec(ast, &env);
		ft_free_ast(&ast);
		free(gwd);
	}
	rl_clear_history();
	// (void)env;
	// tmp = get_next_line(0);
	// if (ft_parsing(tmp) != 0)
	// 	return ; //gnl a supp, pour mieux verif valgrind
	// ft_free_ast(&ast);
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
