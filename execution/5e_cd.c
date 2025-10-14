/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5e_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:43:20 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/10 00:51:59 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cd_path(char **args, t_env **env, int *should_print)
{
	char	*path;

	*should_print = 0;
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = get_env_value(*env, "HOME");
		if (!path)
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = get_env_value(*env, "OLDPWD");
		if (!path)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		else
			*should_print = 1;
	}
	else
		path = args[1];
	return (path);
}

static int	handle_cd_error(char *oldpwd, char *path, int return_code)
{
	if (path && return_code != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(path);
	}
	free(oldpwd);
	return (return_code);
}

static int	update_single_env_var(t_env **env, char *key, char *value)
{
	t_env	*current;

	if (!value)
		return (0);
	current = *env;
	while (current && ft_strcmp(current->key, key) != 0)
		current = current->next;
	if (!current)
		return (0);
	free(current->value);
	current->value = ft_strdup(value);
	if (!current->value)
		return (0);
	return (1);
}

static void	update_pwd_env(char *oldpwd, t_env **env)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		free(oldpwd);
		return ;
	}
	update_single_env_var(env, "OLDPWD", oldpwd);
	update_single_env_var(env, "PWD", newpwd);
	free(newpwd);
	free(oldpwd);
}

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
