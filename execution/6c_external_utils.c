/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6c_external_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:24:28 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/30 02:55:40 by qrajendr         ###   ########.fr       */
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

int	check_permission_denied(char *arg)
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

int	handle_dollar_pwd(char **args, t_env *env)
{
	char		*pwd_value;
	struct stat	stat_buf;

	if (ft_strcmp(args[0], "$PWD") == 0)
	{
		pwd_value = get_env_value(env, "PWD");
		if (pwd_value)
		{
			if (stat(pwd_value, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(pwd_value, STDERR_FILENO);
				ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
				return (126);
			}
		}
	}
	return (0);
}
