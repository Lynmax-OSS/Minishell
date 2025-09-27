/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5d_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:51:32 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 17:12:24 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (arg[i] == '\0')
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_with_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit(255);
}

int	ft_exit(char **args, t_env **env)
{
	int	status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (env && *env)
		cleanup_shell(*env);
	if (!args[1])
		exit(g_exit_code);
	if (!is_valid_number(args[1]))
		exit_with_error(args[1]);
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	status = ft_atoi(args[1]) % 256;
	if (status < 0)
		status += 256;
	exit(status);
}
