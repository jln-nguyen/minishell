/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/12 16:11:21 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_envadd_back(t_env **head, t_env *new)
{
	t_env	*last;

	if (!head || !new)
		return ;
	if (*head)
	{
		last = ft_lstlast(*head);
		last->next = new;
	}
	else
		*head = new;
}

t_env	*new_node_env(char *envp)
{
	t_env	*node;
	char	**tmp;
	int		i;

	i = 0;
	node = NULL;
	tmp = NULL;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	while (envp[i] != '=')
		i++;
	node->key = malloc(sizeof(char) * (i + 1));
	if (!node->key)
		return (NULL);
	node->key = ft_strlcpy(node->key, envp, i);
	node->value = malloc(sizeof(char) * (ft_strlen(envp) - i));
	if (!node->value)
		return (NULL);
	node->value = ft_strcpy(node->value, &envp[i]);
	node->next = NULL;
	return (node);
}

void	ft_expand_env(t_env **env, char **envp, int i)
{
	t_env	*node;

	node = NULL;
	while (envp[i])
	{
		node = new_node_env(envp[i]);
		if (!node)
			return (NULL);
		ft_envadd_back(&env, node);
		i++;
	}
}

t_env	*ft_getenv(char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	if (!env)
		return (NULL);
	if (!envp)
		env = ft_create_env();
	env = new_node_env(envp[i]);
	if (!env)
		return (NULL);
	i++;
	return (env);
}

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
	t_env		*env;
	t_ast_node	*ast;
	char		*tmp;

	env = NULL;
	tmp = NULL;
	tok = NULL;
	ast = NULL;
	(void)ac;
	env = ft_getenv(envp);
	
	(void)av;
	tmp = prompt();
	check_syntax(tmp);
	tok = ft_token(tmp);
	print_token(tok); //a supp
	free(tmp);
	ast = parsing_token(tok, -1);
	ft_free(&tok);
	generate_ast_diagram(ast); // a supp
	ft_free_ast(&ast);
	return (0);
}
