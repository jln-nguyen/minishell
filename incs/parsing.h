/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:11:39 by junguyen          #+#    #+#             */
/*   Updated: 2024/12/18 19:02:16 by junguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

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
	int					fd_heredoc;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

char		*change_value(char *tok, t_env *env);
char		*handle_double_quote(char *str, int i, t_env *env);
char		*ft_pre_bigjoin(char *new_str, char **tmp, int i, int j);
char		*ft_strbigjoin(const char *s1, const char *s2, const char *s3);
char		*ft_pre_bigjoin_trim(char *new_str, char **tmp, int i, int j);
char		*remove_quote(char *str, int i, char c);
char		*change_str(char *new_str, int i, t_env *env);
char		*handle_quote(char *str, int i, int j);

int			check_syntax(char *str);
int			move_index(t_token *tok);
int			move_to_end_quote(char *str, char c);
int			ft_is_space(char str);
int			expand_env(t_env **env, char *str_key, char *str_val);
int			check_tok(t_token *tok);
t_token		*new_tok(t_enum_type type, char *str);
t_token		*ft_token(char *str, t_env *env);
t_token		*ft_del_last(t_token *tok);
t_token		*check_env_var(char *str);
t_token		*expand_str(t_token *tok, t_env *env);

t_ast_node	*ft_parsing(char *cmd, t_env *env);
t_ast_node	*parsing_token(t_token *tok, t_enum_type limit);
t_ast_node	*parse_str(t_token *tok, t_enum_type limit);
t_ast_node	*parse_pipe(t_token pipe, t_token *tok);
t_ast_node	*parse_redir_out(t_token op, t_token *tok);
t_ast_node	*new_node(t_enum_type type);
t_ast_node	*check_pipe(t_token *tok, t_enum_type limit);

t_env		*ft_getenv(char **envp);
t_env		*ft_create_env(void);
t_env		*new_env(char *str_key, char *str_val);

void		expand_ast(t_ast_node **ast, t_token *tok,
				t_enum_type limit, char c);
void		ft_tokadd_back(t_token **lst, t_token *new);
void		ft_free(t_token **tok);
void		ft_free_ast(t_ast_node **tok);
void		ft_free_env(t_env **env);
void		ft_free_tab_var_env(char ***tab);
void		ft_tokadd_back(t_token **lst, t_token *new);
void		add_node(t_ast_node **lst, t_ast_node *new, char c);
void		ft_envadd_back(t_env **head, t_env *new);
void		check_whitespace(char **tmp);

void		print_token(t_token *tok); //a supp
void		print_ast(t_ast_node *ast);
void		generate_ast_diagram(t_ast_node *root);
void		print_env(t_env *env);

#endif 