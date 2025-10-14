/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2a_pipe_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:02:14 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/10 01:31:58 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_commands(t_cmd *head)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static int	**setup_pipes(int num_commands)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (num_commands - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < num_commands - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror("minishell: pipe");
			cleanup_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	init_pipeline(t_cmd *head, t_pipe *data)
{
	data->num_commands = count_commands(head);
	data->pipes = setup_pipes(data->num_commands);
	data->pids = NULL;
	data->commands_executed = 0;
	if (data->pipes)
	{
		data->pids = malloc(sizeof(int) * (data->num_commands));
		if (!data->pids)
		{
			cleanup_pipes(data->pipes, data->num_commands - 1);
			data->pipes = NULL;
		}
	}
}
