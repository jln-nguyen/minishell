/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/12 17:45:01 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*tmp;

	tmp = NULL;
	tmp = get_next_line(0);
	if (!tmp)
		return (NULL);
	return (tmp);
}

void	free_struc(t_ast_node **ast, t_env **env, t_token **tok)
{
	ft_free(tok);
	ft_free_ast(ast);
	ft_free_env(env);
}

int	main(int ac, char **av, char **envp)
{
	t_token		*tok;
	t_env		*env;
	t_ast_node	*ast;
	char		*tmp;

	(void)ac;
	(void)av;
	tmp = prompt();
	if (!tmp)
		return (-1);
	env = ft_getenv(envp);
	if (!env)
		return (-2);
	if (check_syntax(tmp) != 0)
		return (free(tmp), ft_free_env(&env), -3);
	tok = ft_token(tmp);
	if (!tok)
		return (-4);
	print_token(tok); //a supp
	free(tmp);
	ast = parsing_token(tok, -1);
	if (!ast)
		return (ft_free_env(&env), -5);
	generate_ast_diagram(ast); // a supp
	free_struc(&ast, &env, &tok);
	return (0);
}
