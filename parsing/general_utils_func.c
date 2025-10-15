/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:07:17 by keteo             #+#    #+#             */
/*   Updated: 2025/08/01 16:07:17 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	skip_whitespace(char **line)
{
	while (**line && is_whitespace(**line))
		(*line)++;
}

int	is_redir(const char *s)
{
	return (!ft_strncmp(s, ">", 2) || !ft_strncmp(s, "<", 2)
		|| !ft_strncmp(s, ">>", 3) || !ft_strncmp(s, "<<", 3));
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	int		len;
	int		i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	result[i] = c;
	result[i + 1] = '\0';
	return (result);
}
