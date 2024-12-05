/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:18:15 by bvictoir          #+#    #+#             */
/*   Updated: 2024/12/05 17:58:28 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libft.h"
# include "parsing.h"

void	ft_pwd(void);
void	ft_env(t_env **env);
void	ft_print_export(t_env **env);
void	ft_unset(t_env **env, t_ast_node *tok);
void	ft_export(t_env **env, t_ast_node *tok);

#endif