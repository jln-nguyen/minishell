/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:17:43 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/22 14:59:01 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_err(char *str)
{
	ft_printf(STDERR_FILENO, "Minishell: ");
	ft_printf(STDERR_FILENO, "%s: error retrieving current directory:", str);
	ft_printf(STDERR_FILENO, " getcwd: cannot access parent directories:");
	ft_printf(STDERR_FILENO, " No such file or directory\n");
	return (EXIT_FAILURE);
}

int	ft_pwd(t_ast_node *ast)
{
	char	*pwd;
	int		i;

	i = 1;
	if (ast->args[1] && ast->args[1][0] == '-')
	{
		while (ast->args[1][i] == '-')
			i++;
		if (ast->args[1][i] != '\0' || i > 2)
		{
			pwd = ft_substr(ast->args[1], 0, 2);
			printf("Minishell: pwd: %s: invalid option\n", pwd);
			free(pwd);
			return (2);
		}
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (pwd_err("pwd"));
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
