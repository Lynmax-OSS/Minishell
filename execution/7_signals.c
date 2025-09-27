/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:51:19 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/27 13:18:02 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_interrupt(int sig)
{
	if (sig == SIGINT)
	{
		write (STDERR_FILENO, "/n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN);
}
