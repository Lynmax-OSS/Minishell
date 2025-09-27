/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:12:31 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 19:44:18 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	restore_std_fds(int save_fds[2])
{
	dup2(save_fds[0], STDIN_FILENO);
	dup2(save_fds[1], STDOUT_FILENO);
	close(save_fds[0]);
	close(save_fds[1]);
}

static int	setup_redirections(t_cmd *cmd, t_env *env, int save_fds[2])
{
	save_fds[0] = dup(STDIN_FILENO);
	save_fds[1] = dup(STDOUT_FILENO);
	if (save_fds[0] == -1 || save_fds[1] == -1)
	{
		perror("minishell: dup");
		g_exit_code = 1;
		return (0);
	}
	if (apply_redirections(cmd->redir, *env) != 0)
	{
		restore_std_fds(save_fds);
		g_exit_code = 1;
		return (0);
	}
	return (1);
}

int	execution(t_cmd *head, t_env **env)
{
	int	status;
	int	save_fds[2];

	if (!head || !head->args || !head->args[0])
		return (0);
	if (head->next)
		return (execution_pipeline(head, *env));
	if (!setup_redirections(head, *env, save_fds))
		return (1);
	if (is_builtin(head->args))
		status = run_builtin(head->args, env);
	else
		status = run_external(head->args, *env);
	restore_std_fds(save_fds);
	g_exit_code = status;
	free_cmd_list(head);
	return (status);
}
