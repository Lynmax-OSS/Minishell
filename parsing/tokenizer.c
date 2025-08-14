/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:21 by keteo             #+#    #+#             */
/*   Updated: 2025/08/13 13:00:21 by keteo            ###   ########.fr       */
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

static void	extract_and_assign(t_token *tokens, char **cursor, int i)
{
	if (**cursor == '\'' || **cursor == '"')
	{
		tokens[i].value = extract_quoted(cursor, **cursor);
		tokens[i].type = TOK_WORD;
	}
	else if (is_operator(**cursor))
	{
		tokens[i].value = extract_operator_str(cursor);
		tokens[i].type = classify_operator(tokens[i].value);
	}
	else
	{
		tokens[i].value = extract_word(cursor);
		tokens[i].type = TOK_WORD;
	}
}

t_token	*tokenizer(char *input, int *count)
{
	t_token	*tokens;
	int		i;
	char	*cursor;

	cursor = input;
	tokens = malloc(sizeof(t_token) * MAX_TOKENS);
	i = 0;
	while (*cursor)
	{
		skip_whitespace(&cursor);
		if (!*cursor)
			break ;
		extract_and_assign(tokens, &cursor, i);
		i++;
	}
	*count = i;
	return (tokens);
}
