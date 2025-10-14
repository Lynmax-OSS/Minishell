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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		count;
	t_token	*tokens;
	t_cmd	*cmd_line;
	t_env	*env;
	int		exec_status;

	(void)ac;
	(void)av;
	// count = 0;
	env = init_env(envp);
	setup_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		count = 0; //
		tokens = tokenizer(line, &count);
		if (!tokens) // safety check
		{
			free(line);
			continue ;
		}
		expand_tokens(tokens, count, env);
		cmd_line = token_parser(tokens, count);
		if (cmd_line)
			exec_status = execution(cmd_line, &env);
		else
			exec_status = 0;
		g_exit_code = exec_status;;
		// while (count--)
		// 	free(tokens[count].value);
		while (count > 0) // safer cleanup
			free(tokens[--count].value);
		free(tokens);
		free(line);
	}
	cleanup_shell(env);
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
