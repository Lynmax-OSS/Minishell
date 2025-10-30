/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6c_external_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:24:28 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/31 05:42:49 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

char	*search_in_path(char *cmd, t_env *env)
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

int	handle_directory_error(char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	return (126);
}

int	check_expanded_directory(char *path, t_env *env)
{
	struct stat	path_stat;
	char		*expanded_path;

	if (path[0] == '$')
	{
		expanded_path = expand_single_var(path + 1, env);
		if (expanded_path && expanded_path[0] != '\0')
		{
			if (stat(expanded_path, &path_stat) == 0
				&& S_ISDIR(path_stat.st_mode))
			{
				free(expanded_path);
				return (handle_directory_error(path));
			}
		}
		free(expanded_path);
	}
	return (0);
}
