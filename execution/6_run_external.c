/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_run_external.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:57:26 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/30 02:55:32 by qrajendr         ###   ########.fr       */
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

static int	check_if_directory(char *path)
{
	struct stat	path_stat;

	if (ft_strchr(path, '/') && stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			return (126);
		}
	}
	return (0);
}

static int	handle_no_cmd_path(char *arg)
{
	if (ft_strcmp(arg, "$PWD") == 0)
		ft_putstr_fd("minishell: $PWD: No such file or directory\n",
			STDERR_FILENO);
	else if (ft_strchr(arg, '/') && access(arg, F_OK) == 0)
		ft_putstr_fd("minishell: Permission denied\n", STDERR_FILENO);
	else if (ft_strchr(arg, '/'))
		ft_putstr_fd("minieshell: No such file or directory\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	if (ft_strcmp(arg, "$PWD") == 0 || ft_strchr(arg, '/'))
		return (127);
	return (127);
}

int	run_external(char **args, t_env *env)
{
	char		*cmd_path;
	char		**env_array;
	int			status;

	if (!args || !args[0])
		return (1);
	status = handle_dollar_pwd(args, env);
	if (status)
		return (status);
	status = check_permission_denied(args[0]);
	if (status)
		return (status);
	status = check_if_directory(args[0]);
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
