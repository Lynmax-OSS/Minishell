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

void	print_tokens(t_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("Token[%d]: value=\"%s\", type=%d\n",
			i, tokens[i].value, tokens[i].type);
		i++;
	}
}

static void print_redirs(t_redir *redir)
{
    while (redir)
    {
        printf("    redir: type=%s, target=%s\n",
            redir->type, redir->target);
        redir = redir->next;
    }
}

void print_cmd_list(t_cmd *cmds)
{
    int j;

    while (cmds)
    {
        j = 0;
        printf("Command:\n");
        while (cmds->args && cmds->args[j])
        {
            printf("    arg[%d]: %s\n", j, cmds->args[j]);
            j++;
        }
        print_redirs(cmds->redir);
        cmds = cmds->next;
        if (cmds)
            printf("---- pipe ----\n");
    }
}

int	main(void)
{
	char	*line;
	int		count;
	t_token	*tokens;
	t_cmd	*cmd_line;

	count = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = tokenizer(line, &count);
		cmd_line = token_parser(tokens, count);
		if (cmd_line)
			print_cmd_list(cmd_line);
		while (count--)
			free(tokens[count].value);
		free(tokens);
		free(line);
	}
	printf("exit\n");
	return (0);
}
