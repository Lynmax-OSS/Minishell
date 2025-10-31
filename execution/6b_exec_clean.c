/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6b_exec_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:24:22 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/31 17:22:25 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_child(char *cmd_path, char **args, char **env_array)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd_path, args, env_array);
	perror("minishell");
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES)
		exit(126);
	else
		exit(1);
}

static int	execute_parent(pid_t pid, char *cmd_path, char **env_array)
{
	int	status;

	free(cmd_path);
	free_string_array(env_array);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_and_cleanup(char *cmd_path, char **args, char **env_array)
{
	pid_t	pid;
	int		parent_signal;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		free(cmd_path);
		free_string_array(env_array);
		return (1);
	}
	if (pid == 0)
		execute_child(cmd_path, args, env_array);
	parent_signal = execute_parent(pid, cmd_path, env_array);
	return (parent_signal);
}
