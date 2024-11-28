/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:18:15 by bvictoir          #+#    #+#             */
/*   Updated: 2024/11/28 11:20:41 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libft.h"
# include "parsing.h"

void	ft_pwd(void);
void	ft_env(t_env **env);
void	ft_print_export(t_env **env);
void	ft_unset(t_env **env, t_token *tok);
void	ft_export(t_env **env, t_token *tok);

#endif