/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_wait_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 08:29:39 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/24 12:21:58 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	wait_all_children(int *pids, int num_children)
{
	int	i;
	int	status;
	int	exit_status;

	if (!pids || num_children <= 0)
		return (0);
	i = 0;
	exit_status = 0;
	while (i < num_children)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (exit_status);
}
