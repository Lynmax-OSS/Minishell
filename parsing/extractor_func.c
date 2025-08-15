/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:32:40 by keteo             #+#    #+#             */
/*   Updated: 2025/08/14 12:32:40 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_quoted(char **line, char quote)
{
	char	*start;
	int		len;
	char	*result;

	(*line)++;
	start = *line;
	len = 0;
	while (**line && **line != quote)
	{
		len++;
		(*line)++;
	}
	result = ft_strndup(start, len);
	if (**line == quote)
		(*line)++;
	return (result);
}

char	*extract_word(char **line)
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

char	*extract_operator_str(char **line)
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
