/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4c_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:57:36 by qrajendr          #+#    #+#             */
/*   Updated: 2025/10/30 03:11:46 by qrajendr         ###   ########.fr       */
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

static char	*handle_variable(t_heredoc heredoc, char *line, t_env *env)
{
	char	*var_name;
	char	*var_value;
	char	*temp;

	var_name = ft_substr(line, heredoc.i + 1, heredoc.j - (heredoc.i + 1));
	if (!var_name)
		return (heredoc.new);
	var_value = get_env_value(env, var_name);
	free(var_name);
	if (var_value)
	{
		temp = ft_strjoin(heredoc.new, var_value);
		free(heredoc.new);
		heredoc.new = temp;
	}
	return (heredoc.new);
}

char	*expand_heredoc_line(char *line, t_env *env)
{
	t_heredoc	heredoc;

	if (!line)
		return (NULL);
	heredoc.new = ft_strdup("");
	heredoc.i = 0;
	while (line && line[heredoc.i])
	{
		if (line[heredoc.i] == '$' && is_valid_var_char(line[heredoc.i + 1]))
		{
			heredoc.j = find_var_end(line, heredoc.i + 1);
			heredoc.new = handle_variable(heredoc, line, env);
			heredoc.i = heredoc.j;
		}
		else
			heredoc.new = join_char(heredoc.new, line[heredoc.i++]);
	}
	return (heredoc.new);
}
