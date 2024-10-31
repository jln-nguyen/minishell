/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/10/30 19:43:29 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	main(int ac, char **av, char **envp)
{
	t_token	*tok;

	tok = NULL;
	(void)ac;
	(void)envp;
	check_syntax(av[1]);
	tok = ft_token(av[1]);
	print_token(tok);
	ft_free(&tok);
	return (0);
}
