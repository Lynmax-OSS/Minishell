/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5g2_update_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:34:00 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 11:34:02 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*find_existing_var(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static void	add_new_variable(t_env **env, char *key, char *value)
{
	t_env	*new_var;

	if (!value)
	{
		value = ft_strdup("");
		if (!value)
		{
			free(key);
			return ;
		}
	}
	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		free(key);
		free(value);
		return ;
	}
	new_var->key = key;
	new_var->value = value;
	new_var->next = *env;
	*env = new_var;
}

void	update_env_variable(t_env **env, char *key, char *value)
{
	t_env	*existing;

	existing = find_existing_var(*env, key);
	if (existing)
	{
		if (value)
		{
			free(existing->value);
			existing->value = value;
		}
		free(key);
		return ;
	}
	add_new_variable(env, key, value);
}
