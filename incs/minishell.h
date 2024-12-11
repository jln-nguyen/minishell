/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:14:14 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/11 11:06:22 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec.h"
# include "parsing.h"
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>

void		ft_cd(char *str, t_env	**env);
void		ft_exec(t_ast_node **ast, t_env **env);
void		ft_echo(char **args);
void		ft_execve(char **env, char **cmd);
void		exec_cmd(t_ast_node **ast, t_env **env);
void		ft_redir(t_ast_node **ast, t_env **env);

int			ft_check_builtins(t_ast_node *ast, t_env **env);
int			ft_redir_out(t_ast_node *ast);
int			ft_redir_in(t_ast_node *ast, t_env **env);
int			ft_heredoc(t_ast_node *ast, t_env **env);

char		*find_path(char *cmd, char **env);
char		**struc_to_char(t_env *env);

void		search_cmd(t_ast_node **ast);

#endif