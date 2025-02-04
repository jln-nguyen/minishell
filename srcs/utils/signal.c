/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:01:42 by junguyen          #+#    #+#             */
/*   Updated: 2025/02/03 16:08:04 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sig(int signal)
{
	(void)signal;
	g_signal = 130;
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
	rl_on_new_line();
	rl_done = 1;
}

void	sigint_process(int signal)
{
	if (signal == SIGQUIT)
		printf("Quit (core dumped)\n");
}

void	sigint_handler(int signal)
{
	(void)signal;
	g_signal = 130;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int signal)
{
	(void)signal;
	g_signal = 131;
	printf("Quit (core dumped)\n");
	rl_on_new_line();
	rl_redisplay();
}
