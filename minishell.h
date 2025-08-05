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
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct	s_redir
{
	char			*type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct	s_cmd
{
	char		**args;
	t_redir		*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_data
{
	int		start;
	int		len;
	char	**args;
}	t_data;

char	*extract_regular_token(char **line);
char	*extract_operator(char **line);
char	*extract_double_quote(char **line);
char	*extract_single_quote(char **line);
int		is_whitespace(char c);
int		is_operator(char c);
int		is_redir(const char *s);
void	skip_whitespace(char **line);
char	**tokenizer(char *input);

#endif