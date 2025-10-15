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

static void	extract_and_assign(t_token *tokens, char **cursor, int i)
{
	char	*save_pos;
	char	*before;

	tokens[i].quoted = 0;
	save_pos = *cursor;
	if (is_operator(**cursor))
		
	else if (**cursor == '\'' && !is_operator(*(*cursor + 1)))
	{
		tokens[i].value = extract_quoted(cursor, **cursor);
		tokens[i].type = TOK_WORD;
		tokens[i].quoted = 1;
	}
	else if (**cursor == '"' && !is_operator(*(*cursor + 1)))
	{
		before = *cursor;
		tokens[i].value = extract_quoted(cursor, **cursor);
		if (**cursor && !is_whitespace(**cursor) && !is_operator(**cursor))
		{
			free(tokens[i].value);
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
