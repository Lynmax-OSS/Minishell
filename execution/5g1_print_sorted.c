/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5g1_print_sorted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:34:25 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 11:34:26 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static t_env	**env_list_to_array(t_env *env, int size)
{
	t_env	**array;
	int		i;

	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		array[i++] = env;
		env = env->next;
	}
	return (array);
}

static void	sort_env_array(t_env **array, int size)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted_variables(t_env *env)
{
	int		size;
	t_env	**array;
	int		i;

	size = env_list_size(env);
	array = env_list_to_array(env, size);
	if (!array)
		return ;
	sort_env_array(array, size);
	i = 0;
	while (i < size)
	{
		if (array[i]->value)
			printf("declare -x %s=\"%s\"\n", array[i]->key, array[i]->value);
		else
			printf("declare -x %s\n", array[i]->key);
		i++;
	}
	free(array);
}
