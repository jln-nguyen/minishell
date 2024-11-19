/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/19 18:31:39 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_struc(t_ast_node **ast, t_token **tok)
// {
// 	ft_free(tok);
// 	ft_free_ast(ast);
// 	// ft_free_env(env);
// }

int	ft_parsing(char *cmd, t_env *env)
{
	t_ast_node	*ast;
	t_token		*tok;

	if (check_syntax(cmd) != 0)
		return (free(cmd), -3);
	tok = ft_token(cmd);
	if (!tok)
		return (free(cmd), -4);
	print_token(tok); //a supp
	free(cmd);
	ast = parsing_token(tok, -1);
	if (!ast)
		return (ft_free_env(&env), -5);
	generate_ast_diagram(ast); // a supp
	ft_free(&tok);
	ft_free_ast(&ast);
	return (0);
}

void	prompt(t_env *env)
{
	char	*tmp;

	tmp = NULL;
	write(1, "Minishell$ ", 12);
	// while (get_next_line(0) != NULL)
	// {
		tmp = get_next_line(0);
		if (!tmp)
			return ;
		if (ft_parsing(tmp, env) != 0)
			return ;
		// free(tmp);
		// write(1, "Minishell$ ", 12);
	// }
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
	// tmp = prompt();
	// if (!tmp)
	// 	return (-1);
	ft_free_env(&env);
	return (0);
}
