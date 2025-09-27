/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_redirections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 09:00:01 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 15:58:58 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//main redirection function

int	apply_redirections(t_redir *redir, t_env *env)
{
	t_redir	*current;
	int		result;

	if (!redir)
		return (0);
	current = redir;
	while (current)
	{
		result = handle_single_redirection(current, env);
		if (result != 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
