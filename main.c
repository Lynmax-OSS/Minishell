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

// void	print_tokens(t_token *tokens, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		printf("Token[%d]: value=\"%s\", type=%d\n",
// 			i, tokens[i].value, tokens[i].type);
// 		i++;
// 	}
// }

// static void print_redirs(t_redir *redir)
// {
// 	while (redir)
// 	{
// 		printf("    redir: type=%s, target=%s\n",
// 			redir->type, redir->target);
// 		redir = redir->next;
// 	}
// }

// void print_cmd_list(t_cmd *cmds)
// {
// 	int j;

// 	while (cmds)
// 	{
// 		j = 0;
// 		printf("Command:\n");
// 		while (cmds->args && cmds->args[j])
// 		{
// 			printf("    arg[%d]: %s\n", j, cmds->args[j]);
// 			j++;
// 		}
// 		print_redirs(cmds->redir);
// 		cmds = cmds->next;
// 		if (cmds)
// 			printf("---- pipe ----\n");
// 	}
// }

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

// void	print_env_list(t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		printf("%s=%s\n", tmp->key, tmp->value);
// 		tmp = tmp->next;
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env;
// 	t_token	*tokens;
// 	int		count;

// 	(void)argc;
// 	(void)argv;
// 	env = init_env(envp);

// 	// test: print full ENV
// 	printf("=== ENV list ===\n");
// 	print_env_list(env);

// 	// test: tokenize a command with $VAR
// 	char *line = "echo $HOME $USER notvar";
// 	tokens = tokenizer(line, &count);

// 	printf("\n=== Before expansion ===\n");
// 	for (int i = 0; i < count; i++)
// 		printf("Token[%d]: %s\n", i, tokens[i].value);

// 	expand_tokens(tokens, count, env);

// 	printf("\n=== After expansion ===\n");
// 	for (int i = 0; i < count; i++)
// 		printf("Token[%d]: %s\n", i, tokens[i].value);

// 	// cleanup: free tokens and env (not fully shown here)
// 	return (0);
// }
