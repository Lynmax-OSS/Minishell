/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5e1_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:36:14 by keteo             #+#    #+#             */
/*   Updated: 2025/10/15 21:36:14 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cd_path(char **args, t_env **env, int *should_print)
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

int	handle_cd_error(char *oldpwd, char *path, int return_code)
{
	if (path && return_code != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(path);
	}
	free(oldpwd);
	return (return_code);
}

int	update_single_env_var(t_env **env, char *key, char *value)
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

void	update_pwd_env(char *oldpwd, t_env **env)
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

int	check_cd_args(char **args)
{
	int arg_count;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count > 2 || (arg_count == 2 && ft_strchr(args[1], ' ')))
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}