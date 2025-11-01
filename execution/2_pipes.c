/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 08:05:42 by qrajendr          #+#    #+#             */
/*   Updated: 2025/11/02 01:21:56 by qrajendr         ###   ########.fr       */
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

static int	process_all_heredocs(t_cmd *head, t_env *env)
{
	t_cmd	*cur;
	t_redir	*redir;
	int		fd;

	cur = head;
	while (cur)
	{
		redir = cur->redir;
		while (redir)
		{
			if (ft_strcmp(redir->type, "<<") == 0)
			{
				fd = create_heredoc(redir->target, env);
				if (fd == -1)
					return (-1);
				/* store the read-end fd in the redir so children can use it */
				redir->fd = fd;
			}
			redir = redir->next;
		}
		cur = cur->next;
	}
	return (0);
}

static void	close_heredoc_fds(t_cmd *head)
{
	t_cmd    *cur;
	t_redir  *redir;

	cur = head;
	while (cur)
	{
		redir = cur->redir;
		while (redir)
		{
			if (redir->fd >= 0)
			{
				close(redir->fd);
				redir->fd = -1;
			}
			redir = redir->next;
		}
		cur = cur->next;
	}
}

static int	handle_pipeline_cleanup(t_pipe *data, t_cmd *head)
{
	int	status;

	if (data->pipes)
		cleanup_pipes(data->pipes, data->num_commands - 1);
	if (data->pids)
	{
		status = wait_all_children(data->pids, data->commands_executed);
		free(data->pids);
		free_cmd_list(head);
		g_exit_code = status;
		return (status);
	}
	free_cmd_list(head);
	return (1);
}

int	execution_pipeline(t_cmd *head, t_env *env)
{
	t_pipe	data;
	int		status;

	data.env = env;
	init_pipeline(head, &data);
	if (!data.pids || !data.pipes)
		return (free_cmd_list(head), 1);
	if (process_all_heredocs(head, env) == -1)
	{
		cleanup_pipes(data.pipes, data.num_commands - 1);
		return (free(data.pids), free_cmd_list(head), 1);
	}
	execute_all_commands(head, &data);
	/* parent no longer needs stored heredoc fds once children are forked */
	close_heredoc_fds(head);
	if (data.pipes)
		close_all_pipes(data.pipes, data.num_commands - 1);
	status = handle_pipeline_cleanup(&data, head);
	return (status);
}