/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5e_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:43:20 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/17 09:27:55 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char **args, t_env **env)
{
	char	*oldpwd;
	char	*path;
	int		should_print;
	int		ret;
	int		arg_count;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (arg_count == 2 && ft_strchr(args[1], ' ') != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: error getting current directory\n",
			STDERR_FILENO);
		return (1);
	}
	path = get_cd_path(args, env, &should_print);
	if (!path)
		return (handle_cd_error(oldpwd, NULL, 1));
	ret = chdir(path);
	if (ret != 0)
		return (handle_cd_error(oldpwd, path, 1));
	if (should_print)
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	update_pwd_env(oldpwd, env);
	return (0);
}
