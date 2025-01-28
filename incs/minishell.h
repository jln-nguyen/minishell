/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:14:14 by bvictoir          #+#    #+#             */
/*   Updated: 2025/01/28 10:52:44 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

// # define OLDFD_IN 0
// # define FD_HEREDOC 1
// # define OLDFD_OUT 2
// # define FD_OUT 3
// # define FD_IN 4

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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	int			exit_code;
	int			fd_in;
	int			fd_out;
	int			old_fd_in;
	int			old_fd_out;
	t_env		*env;
	t_ast_node	*ast;
}	t_data;

extern int	g_signal;

void		ft_free(t_token **tok);
void		ft_free_env(t_env **env);
void		sigint_handler(int signal);
void		sigint_process(int signal);
void		ft_create_env(t_data *data);
void		sigquit_handler(int signal);
void		check_whitespace(char **tmp);
void		ft_print_export(t_env **env);
void		search_cmd(t_ast_node **ast);
void		ft_free_ast(t_ast_node **tok);
void		ft_free_tab_var_env(char ***tab);
void		ft_exit(t_data *data, char **args);
void		ft_getenv(t_data *data, char **envp);
void		ft_end(t_data *data, int n, char *arg);
void		ft_unset(t_env **env, t_ast_node *tok);
void		ft_exec(t_data *data, t_ast_node **ast);
void		exec_cmd(t_data *data, t_ast_node **ast);
void		ft_redir(t_data *data, t_ast_node **ast);
void		ft_envadd_back(t_env **head, t_env *new);
void		exec_pipe(t_data *data, t_ast_node **ast);
void		ft_reset_fd(int old_fd_in, int old_fd_out);
void		ft_reset_fd(int old_fd_in, int old_fd_out);
void		ft_tokadd_back(t_token **lst, t_token *new);
void		check_heredoc(t_ast_node **ast, t_data *data);
void		error_malloc_tok(t_token **tok, t_data *data);
void		ft_check_heredoc(t_ast_node **ast, t_data *data);
void		add_node(t_ast_node **lst, t_ast_node *new, char c);
void		check_sign(char *n, t_data *data, long *i, int *signe);
void		ft_update_env(t_env **env, char *key, char *value, int bool);
void		ft_no_path(t_data *data, t_ast_node **ast, char **env,
				char *path);
void		expand_ast(t_ast_node **ast, t_token *tok, t_enum_type limit,
				char c);

int			ft_check_builtins(t_data *data, t_ast_node *ast, t_env **env);
int			expand_env(t_data *data, char *str_key, char *str_val);
int			ft_execve(char **env, t_ast_node **ast, t_data *data);
int			ft_redir_in(t_ast_node *ast, t_env **env);
int			ft_export(t_env **env, t_ast_node *tok);
int			expand_lst(t_token **tok, char *str);
int			ft_env(t_ast_node *ast, t_env **env);
int			ft_cd(char **str, t_data *data);
int			ft_redir_out(t_ast_node *ast);
int			move_index(t_token *tok);
int			ft_pwd(t_ast_node *ast);
int			check_tok(t_token *tok);
int			check_syntax(char *str);
int			ft_is_space(char str);
int			ft_echo(char **args);
int			pwd_err(char *str);

long		ft_atol(const char *str);

char		**init_tmp(void);
char		**struc_to_char(t_env *env);
char		*find_path(char *cmd, char **env);
char		*remove_quote(char *str, int *i, char c);
char		*remove_double_quote(char *str, int *i, int j);
char		*ft_pre_bigjoin(char *new_str, char **tmp, int i, int j);
char		*ft_strbigjoin(const char *s1, const char *s2, const char *s3);
char		*change_str(char *new_str, int i, t_data *data, t_token **head);
char		*change_value(char *tok, t_data *data, t_token **head,
				char **split);
char		*handle_double_quote(char *str, int *i, t_data *data,
				t_token **head);

t_token		*ft_del_last(t_token *tok);
t_token		*ft_token(char *str, t_data *data);
t_token		*check_token(char *str, t_token *tok);
t_token		*new_tok(t_enum_type type, char *str);
t_token		*check_token(char *str, t_token *tok);
t_token		*expand_str(t_token *tok, t_data *data);

t_ast_node	*parsing_token(t_token *tok, t_enum_type limit);
t_ast_node	*check_pipe(t_token *tok, t_enum_type limit);
t_ast_node	*parse_str(t_token *tok, t_enum_type limit);
t_ast_node	*parse_redir_out(t_token op, t_token *tok);
t_ast_node	*parse_pipe(t_token pipe, t_token *tok);
t_ast_node	*ft_parsing(char *cmd, t_data *data);
t_ast_node	*new_node(t_enum_type type);

t_env		*new_env(char *str_key, char *str_val);

#endif