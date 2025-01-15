/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:17:43 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/15 18:06:23 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			printf("pwd: %s: invalid option\n", pwd);
			free(pwd);
			return (2);
		}
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
