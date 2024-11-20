/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:11:39 by junguyen          #+#    #+#             */
/*   Updated: 2024/11/20 18:01:45 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "get_next_line.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;


typedef enum e_enum_type
{
	TOKEN_STR,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
}	t_enum_type;

typedef struct s_token
{
	t_enum_type		type;
	char			*value;
	struct s_token	*next;	
}	t_token;

typedef struct s_ast_node
{
	t_enum_type			type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

char		*change_value(char *tok);
char		*handle_double_quote(char *str);
char		*ft_strbigjoin(const char *s1, const char *s2, const char *s3);
char		*handle_quote(char *str);

int			check_syntax(char *str);
int			move_index(t_token *tok, char *str, int i);
int			move_to_end_quote(char *str, char c);
int			ft_parsing(char *cmd, t_env *env);

t_token		*new_tok(t_enum_type type, char *str);
t_token		*ft_token(char *str);
t_token		*ft_del_last(t_token *tok);
t_token		*check_env_var(char *str);
//t_token		*check_quote(char *str, char c);
t_token		*expand_str(t_token *tok);

t_ast_node	*parsing_token(t_token *tok, t_enum_type limit);
t_ast_node	*parse_str(t_token *tok, t_enum_type limit);
t_ast_node	*parse_pipe(t_token pipe, t_token *tok);
t_ast_node	*parse_redir_out(t_token op, t_token *tok);
t_ast_node	*new_node(t_enum_type type);
t_ast_node	*check_pipe(t_token *tok, t_enum_type limit);

t_env		*ft_getenv(char **envp);

void		expand_ast(t_ast_node **ast, t_token *tok,
				t_enum_type limit, char c);
void		ft_tokadd_back(t_token **lst, t_token *new);
void		ft_free(t_token **tok);
void		ft_free_ast(t_ast_node **tok);
void		ft_free_env(t_env **env);
void		ft_free_tab_var_env(char ***tab);
void		ft_tokadd_back(t_token **lst, t_token *new);

void		print_token(t_token *tok); //a supp
void		print_ast(t_ast_node *ast);
void		generate_ast_diagram(t_ast_node *root);

#endif 