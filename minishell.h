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
} t_toktype;

typedef struct s_token
{
	char		*value;
	t_toktype	type;
} t_token;

typedef struct s_redir
{
	char			*type;
	char			*target;
	struct s_redir	*next;
} t_redir;

typedef struct	s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
} t_cmd;


//parsing
int		is_whitespace(char c);
int		is_operator(char c);
int		is_redir(const char *s);
void	skip_whitespace(char **line);
char	*extract_word(char **line);
char	*extract_operator_str(char **line);
char	*extract_quoted(char **line, char quote);
t_token	*tokenizer(char *input, int *count);
t_cmd	*token_parser(t_token *tokens, int count);

//execution
int		execute_commands(t_cmd *head, char **envp);
int		is_builtin(char **args);
int		run_builtin(char **args);
int		apply_redirections(t_redir *redir);
int		run_external(char **args, char **envp);
void    wait_all_children(int *status);

//builtins
int		ft_echo(char **args);
int		ft_exit(char **args);
int		ft_pwd(void);

#endif
