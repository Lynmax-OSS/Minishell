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

int		is_whitespace(char c);
int		is_operator(char c);
int		is_redir(const char *s);
void	skip_whitespace(char **line);
t_token	*tokenizer(char *input, int *count);

#endif