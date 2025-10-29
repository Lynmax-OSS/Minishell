/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5a_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:09:14 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/30 03:12:01 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_echo(char **args, int i, int newline)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	ft_echo(char **args)
{
	int	i;
	int	newline;
	int	j;

	if (!args || !args[0])
		return (1);
	i = 1;
	newline = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	print_echo(args, i, newline);
	g_exit_code = 0;
	return (0);
}
