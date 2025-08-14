/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:21 by keteo             #+#    #+#             */
/*   Updated: 2025/08/13 13:00:21 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_toktype	classify_operator(char *s)
{
	if (!ft_strncmp(s, "|", 2))
		return (TOK_PIPE);
	if (!ft_strncmp(s, ">>", 3))
		return (TOK_DREDIR_OUT);
	if (!ft_strncmp(s, ">", 2))
		return (TOK_REDIR_OUT);
	if (!ft_strncmp(s, "<<", 3))
		return (TOK_DREDIR_IN);
	if (!ft_strncmp(s, "<", 2))
		return (TOK_REDIR_IN);
	return (TOK_WORD);
}

static char	*extract_word(char **line)
{
	char	*start;
	int		len;

	start = *line;
	len = 0;
	while (**line && !is_whitespace(**line) && !is_operator(**line))
	{
		(*line)++;
		len++;
	}
	return (ft_strndup(start, len));
}

static char	*extract_operator_str(char **line)
{
	char	*op;

	if ((**line == '<' && *(*line + 1) == '<')
		|| (**line == '>' && *(*line + 1) == '>'))
	{
		op = ft_strndup(*line, 2);
		*line += 2;
		return (op);
	}
	else
	{
		op = ft_strndup(*line, 1);
		(*line)++;
		return (op);
	}
}

t_token	*tokenizer(char *input, int *count)
{
	t_token	*tokens;
	int		i;

	tokens = malloc(sizeof(t_token) * MAX_TOKENS);
	i = 0;
	while (*input)
	{
		skip_whitespace(&input);
		if (!*input)
			break ;
		if (is_operator(*input))
		{
			tokens[i].value = extract_operator_str(&input);
			tokens[i].type = classify_operator(tokens[i].value);
		}
		else
		{
			tokens[i].value = extract_word(&input);
			tokens[i].type = TOK_WORD;
		}
		i++;
	}
	*count = i;
	return (tokens);
}
