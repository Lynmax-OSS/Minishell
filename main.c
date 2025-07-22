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
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char *line;

	while (1)
	{
		line = readline("minishell> ");
		tokenizer(line);
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
			add_history(line);
		free(line);
	}
	return (0);
}