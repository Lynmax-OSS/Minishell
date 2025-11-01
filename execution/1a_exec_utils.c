/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:13:21 by qrajendr          #+#    #+#             */
/*   Updated: 2025/11/02 01:21:56 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir_tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		while (cmd->redir)
		{
			redir_tmp = cmd->redir->next;
			if (cmd->redir->fd >= 0)
				close(cmd->redir->fd);
			free(cmd->redir->type);
			free(cmd->redir->target);
			free(cmd->redir);
			cmd->redir = redir_tmp;
		}
		free(cmd);
		cmd = tmp;
	}
}

static void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	cleanup_shell(t_env *env)
{
	if (env)
		free_env_list(env);
	rl_clear_history();
}
