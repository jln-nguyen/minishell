/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:18 by junguyen          #+#    #+#             */
/*   Updated: 2025/01/28 12:40:57 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_msg_token(t_token *tok)
{
	ft_printf(STDERR_FILENO, "Minishell: syntax error near unexpected ");
	if (tok->value[0] != '|')
	{
		if ((tok->next && tok->next->value[0] != '|') || !tok->next)
			ft_printf(STDERR_FILENO, "token 'newline'\n");
		else
			ft_printf(STDERR_FILENO, "token '%c'\n", tok->next->value[0]);
	}
	else
		ft_printf(STDERR_FILENO, "token '%c'\n", tok->value[0]);
	return (-1);
}

int	check_tok(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
		return (error_msg_token(tok));
	while (tok->next != NULL)
	{
		if (tok->type != TOKEN_STR && tok->type != TOKEN_ENV_VAR
			&& tok->type != TOKEN_PIPE)
		{
			if (tok->next->type != TOKEN_STR
				&& tok->next->type != TOKEN_ENV_VAR)
				return (error_msg_token(&(*tok)));
		}
		tok = tok->next;
	}
	if (tok->type != TOKEN_STR && tok->type != TOKEN_ENV_VAR)
	{
		if (tok->next == NULL)
			return (error_msg_token(&(*tok)));
	}
	return (0);
}


static t_token	*init_tok(char *str, int *i)
{
	t_token	*tok;
	int		j;

	j = 0;
	tok = NULL;
	while (str[j] && tok == NULL)
	{
		if (str[j] == 32 || (str[j] >= 9 && str[j] <= 13))
			j++;
		else
		{
			tok = check_token(&str[j], tok);
			if (!tok)
			{
				free(str);
				ft_printf(STDERR_FILENO, "Minishell: Malloc error\n");
				exit(EXIT_FAILURE);
			}
			j += move_index(tok);
		}
	}
	*i = j;
	return (tok);
}

t_token	*ft_token(char *str, t_data *data)
{
	int		i;
	t_token	*tok;

	i = 0;
	tok = NULL;
	if (!str)
		return (NULL);
	tok = init_tok(str, &i);
	if (expand_lst(&tok, &str[i]) == -1)
	{
		free(str);
		error_malloc_tok(&tok, data);
	}
	if (check_tok(tok) == -1)
	{
		data->exit_code = 2;
		return (ft_free(&tok), NULL);
	}
	tok = expand_str(tok, data); //j'en suis la
	return (tok);
}

t_ast_node	*ft_parsing(char *cmd, t_data *data)
{
	t_ast_node	*ast;
	t_token		*tok;

	ast = NULL;
	tok = NULL;
	if (check_syntax(cmd) != 0)
		return (data->exit_code = 2, free(cmd), NULL);
	tok = ft_token(cmd, data);
	if (!tok)
		return (free(cmd), NULL);
	free(cmd);
	ast = parsing_token(tok, -1);
	if (!ast)
		return (ft_free(&tok), NULL);
	ft_free(&tok);
	return (ast);
}
