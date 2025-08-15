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

void	print_tokens(t_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("Token[%d]: value=\"%s\", type=%d\n",
			i, tokens[i].value, tokens[i].type);
		i++;
	}
}

int	main(void)
{
	char	*line;
	int		count;
	t_token	*tokens;

	count = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = tokenizer(line, &count);
		print_tokens(tokens, count);
		while (count--)
			free(tokens[count].value);
		free(tokens);
		free(line);
	}
	printf("exit\n");
	return (0);
}
