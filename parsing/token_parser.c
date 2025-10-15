/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:54:10 by keteo             #+#    #+#             */
/*   Updated: 2025/08/14 13:54:10 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*token_parser(t_token *tokens, int count)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*node;
	int		i;

	i = 0;
	head = NULL;
	curr = NULL;
	if (validate_syntax(tokens, count) == -1)
		return (NULL);
	while (i < count)
	{
		node = cmd_list_init(tokens, &i, count);
		if (i < count && tokens[i].type == TOK_PIPE)
			i++;
		if (!head)
			head = node;
		else
			curr->next = node;
		curr = node;
	}
	return (head);
}
