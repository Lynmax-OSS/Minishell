/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:22:32 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/09 23:31:57 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(args[0], "export") == 0)
		return (1);
	if (ft_strcmp(args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(args[0], "env") == 0)
		return (1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (1);
	return (0);
}

// int	run_builtin(char **args, t_env **env)
// {
// 	if (!args || !args[0])
// 		return (g_exit_code);
// 	if (ft_strcmp(args[0], "echo") == 0)
// 		return (ft_echo(args));
// 	else if (ft_strcmp(args[0], "cd") == 0)
// 		return (ft_cd(args, env));
// 	else if (ft_strcmp(args[0], "pwd") == 0)
// 		return (ft_pwd());
// 	else if (ft_strcmp(args[0], "export") == 0)
// 		return (ft_export(args, env));
// 	else if (ft_strcmp(args[0], "unset") == 0)
// 		return (ft_unset(args, env));
// 	else if (ft_strcmp(args[0], "env") == 0)
// 		return (ft_env(*env));
// 	else if (ft_strcmp(args[0], "exit") == 0)
// 		return (ft_exit(args, env));
// 	else
// 		return (g_exit_code);
// }

int	run_builtin(char **args, t_env **env)
{
	int	exit_code;

	if (!args || !args[0])
		return (g_exit_code);
	if (ft_strcmp(args[0], "echo") == 0)
		exit_code = ft_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		exit_code = ft_cd(args, env);
	else if (ft_strcmp(args[0], "pwd") == 0)
		exit_code = ft_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		exit_code = ft_export(args, env);
	else if (ft_strcmp(args[0], "unset") == 0)
		exit_code = ft_unset(args, env);
	else if (ft_strcmp(args[0], "env") == 0)
		exit_code = ft_env(*env);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit_code = ft_exit(args, env);
	else
		exit_code = g_exit_code;
	g_exit_code = exit_code;
	return (exit_code);
}