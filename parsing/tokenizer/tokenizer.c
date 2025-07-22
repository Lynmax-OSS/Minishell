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

#include "../minishell.h"

char **tokenizer(const char *input)
{
	char	**token;
	int		i;

	if (!init_token(token))
		perror("Token initialization failed");
	i = 0;
	while (*input)
	{
		if (is_whitespace(&input))
			skip_whitespace(&input);
		else if (*input == '\'')
			token[i++] = extract_single_quote(&input);
		else if (*input == '\"')
			token[i++] = extract_double_quote(&input);
		else if (*input == '>' || *input == '<' || *input == '|')
			token[i++] = extract_operator(&input);
		else
		 	token[i++] = extract_regular_token(&input);
	}
	token[i] = NULL;
	return (token);
}