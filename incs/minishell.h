/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:14:14 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/02 17:20:34 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec.h"
# include "parsing.h"
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>

void	ft_cd(char *str, t_env	**env);
void	ft_exec(t_ast_node *ast, t_env **env);
void	ft_echo(char **args);
void	ft_check_redir(t_ast_node *ast, t_env **env);
void	ft_execve(char **env, char **cmd);
void	exec_cmd(t_ast_node *ast, t_env **env);

#endif