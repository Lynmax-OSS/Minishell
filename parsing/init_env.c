/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:40:12 by keteo             #+#    #+#             */
/*   Updated: 2025/09/12 13:40:12 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*init_env(char **envp)
{
	t_init_env	ini;
	t_env		*new;
	int			i;

	ini.head = NULL;
	i = 0;
	while (envp[i])
	{
		ini.eq = ft_strchr(envp[i], '=');
		if (ini.eq)
		{
			ini.key = ft_substr(envp[i], 0, ini.eq - envp[i]);
			ini.value = ft_strdup(ini.eq + 1);
			new = new_env_node(ini.key, ini.value);
			if (!ini.head)
				ini.head = new;
			else
				ini.cur->next = new;
			ini.cur = new;
		}
		i++;
	}
	return (ini.head);
}
