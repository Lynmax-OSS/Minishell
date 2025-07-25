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
# define MAX_TOKEN 1024

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

char	**tokenizer(const char *input);
int		token_init(char ***token);
char	*extract_double_quotes(char **line);
char	*extract_single_quotes(char **line);
char	*extract_operator(char **line);
char	*extract_regular_token(char **line);
bool	is_operator(char c);

#endif