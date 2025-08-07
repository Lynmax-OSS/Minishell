/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:38:38 by keteo             #+#    #+#             */
/*   Updated: 2025/08/04 15:38:38 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**collect_args(char **tokens, int *i)
{
	t_data	d;

	d.start = *i;
	d.len = 0;
	while (tokens[*i] && ft_strcmp(tokens[*i], "|") && !is_redir(tokens[*i]))
	{
		(*i)++;
		d.len++;
	}
	d.args = malloc(sizeof(char *) * (d.len + 1));
	if (!d.args)
		return (NULL);
	d.len = 0;
	while (d.start < *i)
	{
		d.args[d.len] = ft_strdup(tokens[d.start]);
		d.len++;
		d.start++;
	}
	d.args[d.len] = NULL;
	return (d.args);
}

t_redir	*add_redir(t_redir *list, char *type, char *target)
{
	t_redir	*tmp;
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
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
