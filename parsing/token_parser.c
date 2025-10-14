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

static char	**collect_args(t_token *tokens, int *i, int count)
{
	char	**args;
	int		arg_count;
	int		j;

	arg_count = 0;
	j = *i;
	while (j < count && tokens[j].type != TOK_PIPE)
	{
		if (tokens[j].type == TOK_WORD
			&& ((j == *i) || !is_redir(tokens[j - 1].value)))
		{
			arg_count++;
		}
		j++;
	}
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	arg_count = 0;
	while (*i < count && tokens[*i].type != TOK_PIPE)
	{
		if (tokens[*i].type == TOK_WORD
			&& (*i == 0 || !is_redir(tokens[*i - 1].value)))
		{
			args[arg_count] = ft_strdup(tokens[*i].value);
			arg_count++;
		}
		(*i)++;
	}
	args[arg_count] = NULL;
	return (args);
}

static t_cmd	*cmd_list_init(t_token *tokens, int *i, int count)
{
	t_cmd	*node;
	char	*type;
	char	*target;
	int		start;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	start = *i;
	node->args = collect_args(tokens, i, count);
	node->redir = NULL;
	node->next = NULL;
	*i = start;
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
		{
			(*i)++;
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
