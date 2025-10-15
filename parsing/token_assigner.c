/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assigner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:27:32 by keteo             #+#    #+#             */
/*   Updated: 2025/10/15 14:27:32 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_toktype	classify_operator(char *s)
{
	if (!ft_strncmp(s, "|", 2))
		return (TOK_PIPE);
	if (!ft_strncmp(s, ">>", 3))
		return (TOK_DREDIR_OUT);
	if (!ft_strncmp(s, ">", 2))
		return (TOK_REDIR_OUT);
	if (!ft_strncmp(s, "<<", 3))
		return (TOK_DREDIR_IN);
	if (!ft_strncmp(s, "<", 2))
		return (TOK_REDIR_IN);
	return (TOK_WORD);
}

void	handle_operator_token(t_token *tokens, char **cursor, int i)
{
	tokens[i].quoted = 0;
	tokens[i].value = extract_operator_str(cursor);
	tokens[i].type = classify_operator(tokens[i].value);
}

void	handle_single_quote_token(t_token *tokens, char **cursor, int i)
{
	tokens[i].quoted = 1;
	tokens[i].value = extract_quoted(cursor, **cursor);
	tokens[i].type = TOK_WORD;
}

void	handle_double_quote_token(t_token *tokens, char **cursor, int i)
{
	char	*before;

	tokens[i].quoted = 0;
	before = *cursor;
	tokens[i].value = extract_quoted(cursor, **cursor);
	if (**cursor && !is_whitespace(**cursor)
		&& !is_operator(**cursor))
	{
		free (tokens[i].value);
		*cursor = before;
		tokens[i].value = extract_word(cursor);
		tokens[i].type = TOK_WORD;
	}
	else
	{
		tokens[i].type = TOK_WORD;
		tokens[i].quoted = 2;
	}
}

void	handle_word_token(t_token *tokens, char **cursor, int i)
{
	tokens[i].quoted = 0;
	tokens[i].value = extract_word(cursor);
	tokens[i].type = TOK_WORD;
}