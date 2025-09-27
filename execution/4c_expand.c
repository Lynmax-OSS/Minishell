/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4c_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:57:36 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 16:04:05 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_var_char(char c)
{
	if (ft_isalpha(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

static int	find_var_end(char *line, int start)
{
	int	i;

	i = start;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	return (i);
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

static char	*join_char(char *str, char c)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, len + 1);
	result[len] = c;
	result[len + 1] = '\0';
	free(str);
	return (result);
}

char	*expand_heredoc_line(char *line, t_env *env)
{
	char	*new;
	char	*var;
	char	*value;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	new = ft_strdup("");
	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$' && is_valid_var_char(line[i + 1]))
		{
			j = find_var_end(line, i + 1);
			new = handle_variable(new, line, i, j, env);
			i = j;
		}
		else
			new = join_char(new, line[i++]);
	}
	return (new);
}
