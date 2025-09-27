/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2c_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:06:47 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 12:30:52 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_pipes(int **pipes, int num_commands)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < num_commands)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	close_all_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
