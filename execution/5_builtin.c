/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:22:32 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 17:11:25 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	run_builtin(char **args, t_env **env)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args, env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(*env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args, env));
	else
		return (1);
}
