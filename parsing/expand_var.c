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