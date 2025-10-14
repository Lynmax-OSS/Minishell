/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_run_external.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:57:26 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/10 05:04:17 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*search_in_path(char *cmd, t_env *env)
{
	char	*path;
	char	**dirs;
	char	*full_path;
	int		i;

	path = get_env_value(env, "PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin3(dirs[i], "/", cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_string_array(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_string_array(dirs);
	return (NULL);
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

int	run_external(char **args, t_env *env)
{
	char	*cmd_path;
	char	**env_array;
	int		status;
	struct stat	path_stat;

	if (!args || !args[0])
		return (1);
	if (ft_strchr(args[0], '/') && stat(args[0], &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			return (126);
		}
	}
	cmd_path = find_command_path(args[0], env);
	if (!cmd_path)
	{
		if (ft_strcmp(args[0], "$PWD") == 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return (127);
		}
		else if (ft_strchr(args[0], '/') && access(args[0], F_OK) == 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (126);
		}
		else if (ft_strchr(args[0], '/'))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return (127);
		}
		else
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			return (127);
		}
	}
	env_array = convert_env_to_array(env);
	if (!env_array)
	{
		free(cmd_path);
		return (127);
	}
	status = execute_and_cleanup(cmd_path, args, env_array);
	return (status);
}
