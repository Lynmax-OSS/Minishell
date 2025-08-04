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

#include "../minishell.h"

char	*extract_single_quote(char **line)
{
	char	*start;
	int		len;
	char	*result;

	(*line)++;
	start = *line;
	len = 0;
	while (**line && **line != '\'')
	{
		len++;
		(*line)++;
	}
	if (**line == '\'')
		(*line)++;
	result = ft_strndup(start, len);
	return (result);
}

char	*extract_double_quote(char **line)
{
	char	*start;
	int		len;
	char	*result;

	(*line)++;
	start = *line;
	len = 0;
	while (**line && **line != '\"')
	{
		len++;
		(*line)++;
	}
	if (**line == '\"')
		(*line)++;
	result = ft_strndup(start, len);
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
	char	*start;
	int		len;
	char	*result;

	start = *line;
	len = 0;
	while (**line && !is_whitespace(**line)
		&& !is_operator(**line) && **line != '\'' && **line != '\"')
	{
		len++;
		(*line)++;
	}
	result = ft_strndup(start, len);
	return (result);
}
