/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2b_pipe_setup_fork.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:10:23 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/31 17:39:39 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_redirection(int cmd_index, t_pipe *data)
{
	if (cmd_index > 0)
	{
		dup2(data->pipes[cmd_index - 1][0], STDIN_FILENO);
		close(data->pipes[cmd_index - 1][0]);
	}
	if (cmd_index < data->num_commands - 1)
	{
		dup2(data->pipes[cmd_index][1], STDOUT_FILENO);
		close(data->pipes[cmd_index][1]);
	}
	return (0);
}

static void	close_all_pipes_in_child(t_pipe *data)
{
	int	i;

	i = 0;
	while (i < data->num_commands - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

static void	execute_command_process(t_cmd *cmd, int cmd_index, t_pipe *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (setup_redirection(cmd_index, data) != 0)
		exit(1);
	if (apply_redirections(cmd->redir, data->env) != 0)
		exit(1);
	close_all_pipes_in_child(data);
	if (is_builtin(cmd->args))
		exit(run_builtin(cmd->args, &(data->env)));
	else
		exit(run_external(cmd->args, data->env));
}

int	setup_and_fork_command(t_cmd *cmd, int cmd_index, t_pipe *data)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (-1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		execute_command_process(cmd, cmd_index, data);
	else if (pid > 0)
		return (pid);
	else
	{
		perror("minishell: fork");
		return (-1);
	}
	return (pid);
}
