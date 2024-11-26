/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/26 18:39:07 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_env *env)
{
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		tmp = readline("Minishell> ");
		if (!tmp)
			return ;
		add_history(tmp);
		if (ft_parsing(tmp, env) != 0)
			return ;
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
