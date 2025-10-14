/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5a_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:09:14 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/09 22:44:42 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_putstr_fd(char *s, int fd)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return ;
// 	while (s[i] != '\0')
// 	{
// 		write(fd, &s[i++], 1);
// 	}
// }

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

// void test_ft_echo(void)
// {
//     printf("=== Echo Tests ===\n");
//     // Basic
//     char *args1[] = {"echo", "hello", "world", NULL};
//     ft_echo(args1);
//     // -n flag
//     char *args2[] = {"echo", "-n", "hello", NULL};
//     ft_echo(args2); printf(" [no newline]\n");
//     // Multiple -n flags
//     char *args3[] = {"echo", "-n", "-n", "hello", NULL};
//     ft_echo(args3); printf(" [multiple -n]\n");
//     // Empty echo
//     char *args4[] = {"echo", NULL};
//     ft_echo(args4);
//     // echo with only flags
//     char *args5[] = {"echo", "-n", NULL};
//     ft_echo(args5); printf(" [only -n flag]\n");
//     // Invalid flag (should still print)
//     char *args6[] = {"echo", "-x", "hello", NULL};
//     ft_echo(args6);
// }

// int main(void)
// {
// 	test_ft_echo();
// 	return (0);
// }
