/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:35:01 by keteo             #+#    #+#             */
/*   Updated: 2025/07/22 15:35:01 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

char	*extract_double_quotes(char **line)
{
	char	*result;
	char	*start;
	int		len;

	(*line)++;
	len = 0;
	start = *line;
	while (**line && **line != '\"')
	{
		(*line)++;
		len++;
	}
	result = ft_strndup(start, len);
	if (**line == '\"')
		(*line)++;
	return (result);
}

char	*extract_single_quotes(char **line)
{
	char	*result;
	char	*start;
	int		len;

	(*line)++;
	len = 0;
	start = *line;
	while (**line != '\'')
	{
		len++;
		(*line)++;
	}
	result = ft_strndup(start, len);
	if (**line == '\'')
		(*line)++;
	return (result);
}

char	*extract_operator(char **line)
{
	char	*result;

	if ((**line == '<' && *(*line + 1) == '<')
		 || (**line == '>' && *(*line + 1) == '>'))
	{
		result = ft_strndup(*line, 2);
		*line += 2;
	}
	else
	{
		result = ft_strndup(*line, 1);
		(*line)++;
	}
	return (result);
}

char	*extract_regular_token(char **line)
{
	char	*result;
	char	*start;
	int		len;

	start = *line;
	len = 0;
	while (!is_whitespace(**line) && !is_operator(**line) && **line != '\'' && **line != '\"')
	{
		(*line)++;
		len++;
	}
	result = ft_strndup(start, len);
	return (result);
}