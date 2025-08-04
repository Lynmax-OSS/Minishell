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

char	**tokenizer(char *input)
{
	char	**tokens;
	int		i;

	tokens = malloc(sizeof(char *) * MAX_TOKENS);
	if (!tokens)
		return (NULL);
	i = 0;
	ft_strndup("hello", 5);
	while (*input)
	{
		skip_whitespace(&input);
		if (!*input)
			break ;
		if (*input == '\'')
			tokens[i++] = extract_single_quote(&input);
		else if (*input == '\"')
			tokens[i++] = extract_double_quote(&input);
		else if (is_operator(*input))
			tokens[i++] = extract_operator(&input);
		else
			tokens[i++] = extract_regular_token(&input);
	}
	tokens[i] = NULL;
	return (tokens);
}
