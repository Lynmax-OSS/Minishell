/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:38:42 by keteo             #+#    #+#             */
/*   Updated: 2025/07/21 13:38:42 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **tokenizer(const char *input)
{
	char	**token;
	char	*line;
	int		i;

	line = (char *)input;
	if (!token_init(&token))
	{
		perror("Token initialization failed");
		exit(1);
	}
	i = 0;
	while (*line)
	{
		// printf("Current char: '%c'\n", *input);
		if (is_whitespace(*line))
			skip_whitespace(line);
		else if (*line == '\'')
			token[i++] = extract_single_quotes(&line);
		else if (*line == '\"')
			token[i++] = extract_double_quotes(&line);
		else if (is_operator(*line))
			token[i++] = extract_operator(&line);
		else
		 	token[i++] = extract_regular_token(&line);
	}
	token[i] = NULL;
	return (token);
}