/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:39:17 by keteo             #+#    #+#             */
/*   Updated: 2025/07/15 15:39:17 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		printf("Token[%d]: %s\n", i, tokens[i]);
		i++;
	}
}

int	main(void)
{
	char	*line;
	char	**tokens;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = tokenizer(line);
		print_tokens(tokens);
		free(line);
	}
	printf("exit\n");
	return (0);
}
