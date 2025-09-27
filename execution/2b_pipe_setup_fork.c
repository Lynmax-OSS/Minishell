/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2b_pipe_setup_fork.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:10:23 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 13:30:39 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	setup_redirection(int cmd_index, t_pipe *data)
{
	if (cmd_index > 0)
		dup2(data->pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index < data->num_commands - 1)
		dup2(data->pipes[cmd_index][1], STDOUT_FILENO);
	return (0);
}

static void	close_fds(int *saved_fds)
{
	close(saved_fds[0]);
	close(saved_fds[1]);
}

static void	execute_command_process(t_cmd *cmd, t_pipe *data)
{
	if (is_builtin(cmd->args))
		exit(run_builtin(cmd->args, &(data->env)));
	else
		exit(run_external(cmd->args, data->env));
}

static void	restore_original_io(int *saved_fds)
{
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
}

int	setup_and_fork_command(t_cmd *cmd, int cmd_index, t_pipe *data)
{
	pid_t	pid;
	int		saved_fds[2];

	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	if (saved_fds[0] == -1 || saved_fds[1] == -1)
		return (-1);
	if (setup_redirection(cmd_index, data) != 0)
		return (close_fds(saved_fds), -1);
	if (apply_redirections(cmd->redir, data->env) != 0)
		return (close_fds(saved_fds), -1);
	close_all_pipes(data->pipes, data->num_commands - 1);
	pid = fork();
	if (pid == 0)
		execute_command_process(cmd, data);
	restore_original_io(saved_fds);
	close_fds(saved_fds);
	return (pid);
}
