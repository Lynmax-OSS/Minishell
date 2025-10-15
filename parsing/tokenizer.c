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
	if (is_operator(**cursor))
		handle_operator_token(tokens, cursor, i);
	else if (**cursor == '\'' && !is_operator(*(*cursor + 1)))
		handle_single_quote_token(tokens, cursor, i);
	else if (**cursor == '"' && !is_operator(*(*cursor + 1)))
		handle_double_quote_token(tokens, cursor, i);
	else
		handle_word_token(tokens, cursor, i);
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
