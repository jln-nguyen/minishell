/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/06 17:31:03 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*prompt(void)
{
	char	*tmp;

	tmp = NULL;
	tmp = get_next_line(0);
	if (!tmp)
		return (NULL);
	return (tmp);
}

int	main(int ac, char **av, char **envp)
{
	t_token		*tok;
	t_ast_node	*ast;
	char		*tmp;

	tmp = NULL;
	tok = NULL;
	ast = NULL;
	(void)ac;
	(void)envp;
	(void)av;
	tmp = prompt();
	check_syntax(tmp);
	tok = ft_token(tmp);
	print_token(tok);
	free(tmp);
	ast = parsing_token(tok);
	print_ast(ast);
	ft_free(&tok);
	ft_free_ast(&ast);
	return (0);
}
