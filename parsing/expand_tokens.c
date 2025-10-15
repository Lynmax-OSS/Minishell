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
