/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:38:31 by keteo             #+#    #+#             */
/*   Updated: 2025/08/04 15:38:31 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_token(char **tokens)
{
	t_data	d;
	int		i;

	i = 0;
	d.head = NULL;
	d.curr = NULL;
	while (tokens[i])
	{
		d.node = malloc(sizeof(t_cmd));
		d.node->args = collect_agrs(tokens, i);
		d.node->redir = NULL;
		d.node->next = NULL;
		while (tokens[i] && is_redir(tokens[i]))
			d.node->redir = add_redir(d.node->redir,
					ft_strdup(tokens[i++]), ft_strdup(tokens[i++]));
		if (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
			i++;
		if (!d.head)
			d.head = d.node;
		else
			d.curr->next = d.node;
		d.curr = d.node;
	}
	return (d.head);
}
