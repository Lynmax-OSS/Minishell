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

static t_redir	*add_redir(t_redir *list, char *type, char *target)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->target = target;
	new->next = NULL;
	if (!list)
		return (NULL);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (list);
}

static char	**collect_args(t_token *tokens, int *i, int count)
{
	char	**args;
	int		start;
	int		len;

	start = *i;
	len = 0;
	while (*i < count && tokens[*i].type == TOK_WORD)
	{
		len++;
		(*i)++;
	}
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	len = 0;
	while (start < *i)
	{
		args[len] = ft_strdup(tokens[start].value);
		len++;
		start++;
	}
	args[len] = NULL;
	return (args);
}

static t_cmd	*cmd_list_init(t_token *tokens, int *i, int count)
{
	t_cmd	*node;
	char	*type;
	char	*target;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = collect_args();
	node->redir = NULL;
	node->next = NULL;
	while (*i < count && tokens[*i].type != TOK_PIPE
			&& tokens[*i].type != TOK_WORD)
	{
		type = ft_strdup(tokens[(*i)++].value);
		if (*i < count)
		{
			target = ft_strdup(tokens[(*i)++].value);
			node->redir = add_redir(node->redir, type, target);
		}
	}
	return (node);
}

t_cmd	*token_parser(t_token *tokens, int count)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*node;
	int		i;

	i = 0;
	head = NULL;
	curr = NULL;
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