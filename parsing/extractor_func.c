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

static char	*extract_part(char **line)
{
	char	*start;
	int		len;

	if (**line == '\'' || **line == '"')
		return (extract_quoted(line, **line));
	start = *line;
	len = 0;
	while (**line && !is_whitespace(**line)
		&& !is_operator(**line)
		&& **line != '\''
		&& **line != '"')
	{
		len++;
		(*line)++;
	}
	return (ft_strndup(start, len));
}

char	*extract_word(char **line)
{
	char	*result;
	char	*part;
	char	*temp;

	result = ft_strdup("");
	while (**line && !is_whitespace(**line) && !is_operator(**line))
	{
		part = extract_part(line);
		temp = result;
		result = ft_strjoin(result, part);
		free(temp);
		free(part);
	}
	return (result);
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

char	*extract_var_name(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_strndup(str, i));
}
