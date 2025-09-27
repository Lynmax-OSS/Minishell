/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5b_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:42:59 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/27 14:47:09 by qrajendr         ###   ########.fr       */
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

int	ft_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		ft_putstr_fd(buffer, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	perror("pwd");
	return (1);
}

// #include <stdio.h>

// void test_ft_pwd(void)
// {
//     int result = ft_pwd();
//     printf("%d\n", result);
// }

// int main(void)
// {
//     test_ft_pwd();
//     return 0;
// }
