/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 08:05:42 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/15 17:32:28 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_pipeline_command(t_cmd *cmd, int cmd_index, t_pipe *data)
{
	pid_t	pid;

	pid = setup_and_fork_command(cmd, cmd_index, data);
	if (pid == -1)
	{
		perror("minishell: command setup failed");
		return (-1);
	}
	return (pid);
}

// static void	execute_all_commands(t_cmd *head, t_pipe *data)
// {
// 	t_cmd	*current;
// 	int		cmd_index;

// 	current = head;
// 	cmd_index = 0;
// 	while (current && data->pids)
// 	{
// 		data->pids[cmd_index] = exec_pipeline_command(current, cmd_index, data);
// 		if (data->pids[cmd_index] == -1)
// 			break ;
// 		current = current->next;
// 		cmd_index++;
// 	}
// 	data->commands_executed = cmd_index;
// }

static void	execute_all_commands(t_cmd *head, t_pipe *data)
{
	t_cmd	*current;
	int		cmd_index;

	current = head;
	cmd_index = 0;
	while (current && data->pids)
	{
		data->pids[cmd_index] = exec_pipeline_command(current, cmd_index, data);
		current = current->next;
		cmd_index++;
	}
	data->commands_executed = cmd_index;
}

// int	execution_pipeline(t_cmd *head, t_env *env)
// {
// 	t_pipe		data;
// 	int			status;

// 	data.env = env;
// 	init_pipeline(head, &data);
// 	if (!data.pids || !data.pipes)
// 		return (1);
// 	execute_all_commands(head, &data);
// 	if (data.pipes)
// 	{
// 		close_all_pipes(data.pipes, data.num_commands - 1);
// 		cleanup_pipes(data.pipes, data.num_commands - 1);
// 	}
// 	if (data.pids)
// 	{
// 		status = wait_all_children(data.pids, data.commands_executed);
// 		free(data.pids);
// 		g_exit_code = status;
// 		return (status);
// 	}
// 	return (1);
// }

int	execution_pipeline(t_cmd *head, t_env *env)
{
	t_pipe		data;
	int			status;

	data.env = env;
	init_pipeline(head, &data);
	if (!data.pids || !data.pipes)
	{
		free_cmd_list(head);
		return (1);
	}
	execute_all_commands(head, &data);
	if (data.pipes)
	{
		close_all_pipes(data.pipes, data.num_commands - 1);
		cleanup_pipes(data.pipes, data.num_commands - 1);
	}
	if (data.pids)
	{
		status = wait_all_children(data.pids, data.commands_executed);
		free(data.pids);
		free_cmd_list(head);
		g_exit_code = status;
		return (status);
	}
	return (1);
}
