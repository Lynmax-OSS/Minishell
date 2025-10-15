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

char	**collect_args(t_token *tokens, int *i, int count)
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
