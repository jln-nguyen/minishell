/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/22 18:16:47 by junguyen         ###   ########.fr       */
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
}

int	main(int ac, char **av, char **envp)
{
	t_env		*env;

	(void)ac;
	(void)av;
	env = ft_getenv(envp);
	if (!env)
		return (-2);
	prompt(env);
	ft_free_env(&env);
	return (0);
}
