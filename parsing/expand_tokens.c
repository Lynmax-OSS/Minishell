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

static int	shoud_expand(t_token token)
{
	if (token.type != TOK_WORD)
		return (0);
	if (token.quoted == 1)
		return (0);
	if (ft_strchr(token.value, '$') == NULL)
		return (0);
	return (1);
}

static void	handle_expansion(t_token *token, t_env *env, int i)
{
	char	*expanded;
	char	*var_name;
	char	*value;

	if (i == 0 && token->value[0] == '$')
	{
		var_name = token->value + 1;
		value = get_env_value(env, var_name);
		if (value && value[0] != '\0')
			return ;
	}
	expanded = expand_embedded_vars(token->value, env);
	free (token->value);
	token->value = expanded;
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
		if (shoud_expand(tokens[i]))
			handle_expansion(&tokens[i], env, i);
		i++;
	}
}
