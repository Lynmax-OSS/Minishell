/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:11:34 by keteo             #+#    #+#             */
/*   Updated: 2025/09/12 14:11:34 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*expand_word(char *word, t_env *env)
{
	char	*val;
	char	*key;

	if (word[0] != '$')
		return (ft_strdup(word));
	key = word + 1;
	val = get_env_value(env, key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

void	expand_tokens(t_token *tokens, int count, t_env *env)
{
	int		i;
	char	*expanded;

	i = 0;
	while (i < count)
	{
		if (tokens[i].type == TOK_WORD && tokens[i].value[0] == '$')
		{
			expanded = expand_word(tokens[i].value, env);
			free(tokens[i].value);
			tokens[i].value = expanded;
		}
		i++;
	}
}
