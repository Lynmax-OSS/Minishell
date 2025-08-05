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
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*node;
	int		i;

	i = 0;
	head = NULL;
	curr = NULL;
	while (tokens[i])
	{
		node = malloc(sizeof(t_cmd));
		if (!node)
			return (NULL);
		node->args = collect_agrs();
		node->redir = NULL;
		node->next = NULL;
		while (tokens[i] && is_redir(tokens[i]))
			node->redir = add_redir();
		if (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
			i++;
		if (!head)
			head = node;
		else
			curr->next = node;
		curr = node;
	}
	return (head);
}