/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:02:12 by keteo             #+#    #+#             */
/*   Updated: 2025/10/15 14:02:12 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_single_var(char *var_name, t_env *env)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_exit_code));
	value = get_env_value(env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*expand_embedded_vars(char *str, t_env *env)
{
	char	*result;
	char	*cursor;

	result = ft_strdup("");
	cursor = str;
	while (*cursor)
	{
		if (*cursor == '$' && *(cursor + 1) && *(cursor + 1) != ' '
			&& *(cursor + 1) != '\0' && *(cursor + 1) != '"')
			process_variable(&result, &cursor, env);
		else
		{
			process_char(&result, *cursor);
			cursor++;
		}
	}
	return (result);
}
