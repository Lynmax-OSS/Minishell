/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6a_env_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:24:17 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 19:44:58 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_env_vars(t_env *env)
{
	int		count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**convert_env_to_array(t_env *env)
{
	char	**array;
	char	*entry;
	int		count;
	int		i;

	count = count_env_vars(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env && i < count)
	{
		entry = ft_strjoin3(env->key, "=", env->value);
		if (!entry)
			return ((free_string_array(array)), NULL);
		array[i] = entry;
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}
