/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5g_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:26:14 by qrajendr          #+#    #+#             */
/*   Updated: 2025/09/26 19:42:26 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_export_name(char *arg)
{
	char	*equal_sign;
	char	*name_part;
	int		is_valid;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		name_part = ft_substr(arg, 0, equal_sign - arg);
		is_valid = valid_identifier(name_part);
		free(name_part);
		return (is_valid);
	}
	is_valid = valid_identifier(arg);
	return (is_valid);
}

static void	handle_export_argument(char *arg, t_env **env)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
		if (!key || !value)
		{
			free(key);
			free(value);
			return ;
		}
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
		if (!key)
			return ;
	}
	update_env_variable(env, key, value);
}

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	error_occurred;

	if (!args[1])
	{
		print_sorted_variables(*env);
		return (0);
	}
	i = 1;
	error_occurred = 0;
	while (args[i])
	{
		if (is_valid_export_name(args[i]))
			handle_export_argument(args[i], env);
		else
		{
			print_export_error(args[i]);
			error_occurred = 1;
		}
		i++;
	}
	return (error_occurred);
}
