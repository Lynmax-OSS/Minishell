/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:36:02 by keteo             #+#    #+#             */
/*   Updated: 2025/10/15 15:36:02 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*add_redir(t_redir *list, char *type, char *target)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (list);
	new->type = type;
	new->target = target;
	new->next = NULL;
	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (list);
}

static void	parse_redirection(t_cmd *node, t_token *tokens, int *i, int count)
{
	char	*type;
	char	*target;

	while (*i < count && tokens[*i].type != TOK_PIPE)
	{
		if (is_redir(tokens[*i].value))
		{
			type = ft_strdup(tokens[(*i)++].value);
			if (*i < count && tokens[*i].type == TOK_WORD)
			{
				target = ft_strdup(tokens[(*i)++].value);
				node->redir = add_redir(node->redir, type, target);
			}
		}
		else
			(*i)++;
	}
}

t_cmd	*cmd_list_init(t_token *tokens, int *i, int count)
{
	t_cmd	*node;
	int		start;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->redir = NULL;
	node->next = NULL;
	start = *i;
	node->args = collect_args(tokens, i, count);
	*i = start;
	parse_redirection(node, tokens, i, count);
	return (node);
}
