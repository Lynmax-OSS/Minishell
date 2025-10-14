/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 08:05:42 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/10 03:20:45 by qrajendr         ###   ########.fr       */
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
		// fprintf(stderr, "DEBUG: About to fork command %d\n", cmd_index);
		data->pids[cmd_index] = exec_pipeline_command(current, cmd_index, data);
		// fprintf(stderr, "DEBUG: Command %d forked with PID %d\n", cmd_index, data->pids[cmd_index]);		// if (data->pids[cmd_index] == -1)
		// 	break ;
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

	// fprintf(stderr, "DEBUG: Starting pipeline execution\n");
	
	data.env = env;
	init_pipeline(head, &data);
	
	// fprintf(stderr, "DEBUG: Pipeline initialized with %d commands\n", data.num_commands);
	
	if (!data.pids || !data.pipes)
	{
		// fprintf(stderr, "DEBUG: Pipeline initialization failed\n");
		free_cmd_list(head);
		return (1);
	}
	
	// fprintf(stderr, "DEBUG: About to execute all commands\n");
	execute_all_commands(head, &data);
	
	// fprintf(stderr, "DEBUG: All commands forked, waiting for children\n");
	
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
		// fprintf(stderr, "DEBUG: Pipeline finished with exit code %d\n", status);
		return (status);
	}
	return (1);
}
