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

// static char	*get_env_value(t_env *env, char *key)
// {
// 	while (env)
// 	{
// 		if (ft_strcmp(env->key, key) == 0)
// 			return (env->value);
// 		env = env->next;
// 	}
// 	return (NULL);
// }

static void	process_char(char **result, char c)
{
	char	*temp;

	temp = *result;
	*result = ft_strjoin_char(*result, c);
	free(temp);
}

static void	process_variable(char **result, char **str, t_env *env)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	int		len;

	(*str)++;
	var_name = extract_var_name(*str);
	var_value = expand_single_var(var_name, env);
	temp = *result;
	*result = ft_strjoin(*result, var_value);
	free(temp);
	len = ft_strlen(var_name);
	*str += len;
	free(var_name);
	free(var_value);
}

// static char	*expand_word(char *word, t_env *env)
// {
// 	char	*val;
// 	char	*key;

// 	if (word[0] != '$')
// 		return (ft_strdup(word));
// 	if (ft_strcmp(word, "$?") == 0)
// 		return (ft_itoa(g_exit_code));
// 	key = word + 1;
// 	val = get_env_value(env, key);
// 	if (!val)
// 		return (ft_strdup(""));
// 	return (ft_strdup(val));
// }

void	expand_tokens(t_token *tokens, int count, t_env *env)
{
	int		i;
	char	*expanded;
	char	*var_name;
	char	*value;

	i = 0;
	while (i < count)
	{
		if (tokens[i].type == TOK_WORD && tokens[i].quoted != 1
			&& ft_strchr(tokens[i].value, '$') != NULL)
		{
			if (i == 0 && tokens[i].value[0] == '$')
			{
				var_name = tokens[i].value + 1;
				value = get_env_value(env, var_name);
				if (value && value[0] != '\0')
				{
					i++;
					continue ;
				}
			}
			expanded = expand_embedded_vars(tokens[i].value, env);
			free(tokens[i].value);
			tokens[i].value = expanded;
		}
		i++;
	}
}
