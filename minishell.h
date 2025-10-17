/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:39:32 by keteo             #+#    #+#             */
/*   Updated: 2025/07/15 15:39:32 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_TOKENS 1024

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef enum e_toktype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_DREDIR_IN,
	TOK_DREDIR_OUT
}	t_toktype;

typedef struct s_token
{
	char		*value;
	t_toktype	type;
	int			quoted;
}	t_token;

typedef struct s_redir
{
	char			*type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_init_env
{
	t_env	*head;
	t_env	*cur;
	char	*eq;
	char	*key;
	char	*value;
}	t_init_env;

typedef struct s_pipe
{
	int		num_commands;
	int		**pipes;
	int		*pids;
	t_env	*env;
	int		commands_executed;
}	t_pipe;

typedef struct	s_heredoc
{
	int		i;
	int		j;
	char	*new;
}	t_heredoc;


extern int	g_exit_code;

//parsing
int		validate_syntax(t_token *tokens, int count);
t_env	*init_env(char **envp);
char	*extract_var_name(char *str);
char	*expand_single_var(char *var_name, t_env *env);
void	expand_tokens(t_token *tokens, int count, t_env *env);
char	*expand_embedded_vars(char *str, t_env *env);
t_redir	*add_redir(t_redir *list, char *type, char *target);
t_cmd	*cmd_list_init(t_token *tokens, int *i, int count);
void	process_variable(char **result, char **str, t_env *env);
void	process_char(char **result, char c);

//tokeninzer
char	*extract_word(char **line);
char	*extract_operator_str(char **line);
char	*extract_quoted(char **line, char quote);
t_token	*tokenizer(char *input, int *count);
t_cmd	*token_parser(t_token *tokens, int count);
void	handle_operator_token(t_token *tokens, char **cursor, int i);
void	handle_word_token(t_token *tokens, char **cursor, int i);
void	handle_double_quote_token(t_token *tokens, char **cursor, int i);
void	handle_single_quote_token(t_token *tokens, char **cursor, int i);
void	handle_operator_token(t_token *tokens, char **cursor, int i);

//execution
int		execution(t_cmd *head, t_env **env);

///utils
void	skip_whitespace(char **line);
int		is_whitespace(char c);
int		is_operator(char c);
int		is_redir(const char *s);
char	*get_env_value(t_env *env, char *key);
void	free_cmd_list(t_cmd *cmd);
void	cleanup_shell(t_env *env);
char	*ft_strjoin_char(char *s1, char c);

///pipes
int		execution_pipeline(t_cmd *head, t_env *env);
void	init_pipeline(t_cmd *head, t_pipe *data);
int		setup_and_fork_command(t_cmd *cmd, int cmd_index, t_pipe *data);
void	cleanup_pipes(int **pipes, int num_commands);
void	close_all_pipes(int **pipes, int num_pipes);

///wait children
int		wait_all_children(int *pids, int num_children);

///redirection
int		apply_redirections(t_redir *redir, t_env *env);
int		handle_single_redirection(t_redir *redir, t_env *env);
int		create_heredoc(char *delimiter, t_env *env);
char	*expand_heredoc_line(char *line, t_env *env);
int		setup_redirection(int cmd_index, t_pipe *data);

///builtins
int		is_builtin(char **args);
int		run_builtin(char **args, t_env **env);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_exit(char **args, t_env **env);
int		ft_cd(char **args, t_env **env);
int		check_cd_args(char **args);
void	update_pwd_env(char *oldpwd, t_env **env);
int		update_single_env_var(t_env **env, char *key, char *value);
int		handle_cd_error(char *oldpwd, char *path, int return_code);
char	*get_cd_path(char **args, t_env **env, int *should_print);
int		ft_unset(char **args, t_env **env);
int		ft_export(char **args, t_env **env);
void	print_sorted_variables(t_env *env);
void	update_env_variable(t_env **env, char *key, char *value);
int		valid_identifier(char *arg);


///external
int		run_external(char **args, t_env *env);
char	**convert_env_to_array(t_env *env);
int		execute_and_cleanup(char *cmd_path, char **args, char **env_array);
void	free_string_array(char **array);
char	*ft_strjoin3(char *s1, char *s2, char *s3);

///signal
void	handle_interrupt(int sig);
void	setup_signals(void);

#endif
