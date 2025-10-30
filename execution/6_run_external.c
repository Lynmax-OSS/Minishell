/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_run_external.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:57:26 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/31 05:19:37 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_permission_denied(char *arg)
{
	struct stat	path_stat;

	if (ft_strchr(arg, '/') && stat(arg, &path_stat) == 0)
	{
		if (access(arg, X_OK) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (126);
		}
	}
	return (0);
}

static int	check_if_directory(char *path, t_env *env)
{
	struct stat	path_stat;

	if (ft_strchr(path, '/') && stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (handle_directory_error(path));
	}
	return (check_expanded_directory(path, env));
}

static char	*find_command_path(char *cmd, t_env *env)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (search_in_path(cmd, env));
}

static int	handle_no_cmd_path(char *arg)
{
	if (ft_strchr(arg, '/') && access(arg, F_OK) == 0)
		ft_putstr_fd("minishell: Permission denied\n", STDERR_FILENO);
	else if (ft_strchr(arg, '/'))
		ft_putstr_fd("minishell: No such file or directory\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return (127);
}

int	run_external(char **args, t_env *env)
{
	char		*cmd_path;
	char		**env_array;
	int			status;

	if (!args || !args[0])
		return (1);
	status = check_permission_denied(args[0]);
	if (status)
		return (status);
	status = check_if_directory(args[0], env);
	if (status)
		return (status);
	cmd_path = find_command_path(args[0], env);
	if (!cmd_path)
		return (handle_no_cmd_path(args[0]));
	env_array = convert_env_to_array(env);
	if (!env_array)
		return (free(cmd_path), 127);
	status = execute_and_cleanup(cmd_path, args, env_array);
	return (status);
}
