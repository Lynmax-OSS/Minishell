/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:39:17 by keteo             #+#    #+#             */
/*   Updated: 2025/07/15 15:39:17 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

static void	free_token(t_token *tokens, int count)
{
	while (count > 0)
		free (tokens[--count].value);
	free (tokens);
}

static int	process_line(t_minishell *minishell)
{
	minishell->count = 0;
	minishell->tokens = tokenizer(minishell->line, &minishell->count);
	if (!minishell->tokens)
		return (0);
	expand_tokens(minishell->tokens, minishell->count, minishell->env);
	minishell->cmd_line = token_parser(minishell->tokens, minishell->count);
	if (minishell->cmd_line)
	{
		minishell->exec_status = execution(minishell->cmd_line,
				&minishell->env);
	}
	else
		minishell->exec_status = 0;
	g_exit_code = minishell->exec_status;
	free_token(minishell->tokens, minishell->count);
	return (1);
}

static void	shell_loop(t_minishell *minishell)
{
	while (1)
	{
		minishell->line = readline("minishell> ");
		if (!minishell->line)
			break ;
		if (*minishell->line)
			add_history(minishell->line);
		if (!process_line(minishell))
		{
			free(minishell->line);
			continue ;
		}
		free (minishell->line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;

	(void)ac;
	(void)av;
	minishell.env = init_env(envp);
	setup_signals();
	shell_loop(&minishell);
	cleanup_shell(minishell.env);
	printf("exit\n");
	return (g_exit_code);
}
