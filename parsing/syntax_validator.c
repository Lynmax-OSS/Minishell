/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:53:20 by keteo             #+#    #+#             */
/*   Updated: 2025/09/11 12:53:20 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_redir_error(t_token *token)
{
	if (token->value)
		fprintf(stderr,
			"minishell: syntax error near unexpected token `%s'\n",
			token->value);
	else
		fprintf(stderr,
			"minishell: syntax error near unexpected token `newline'\n");
	return (-1);
}

static int	check_pipe_errors(t_token *tokens, int i, int count)
{
	if (i == 0 || i == count - 1)
	{
		fprintf(stderr,
			"minishell: syntax error near unexpected token `|'\n");
		return (-1);
	}
	if (tokens[i + 1].type == TOK_PIPE)
	{
		fprintf(stderr,
			"minishell: syntax error near unexpected token `|'\n");
		return (-1);
	}
	return (0);
}

static int	check_redir_errors(t_token *tokens, int i, int count)
{
	if (i + 1 >= count || tokens[i + 1].type != TOK_WORD)
		return (print_redir_error(&tokens[i]));
	return (0);
}

int	validate_syntax(t_token *tokens, int count)
{
	int	i;
	int	ret;

	i = 0;
	if (count == 0)
		return (0);
	while (i < count)
	{
		if (tokens[i].type == TOK_PIPE)
			ret = check_pipe_errors(tokens, i, count);
		else if (tokens[i].type == TOK_REDIR_IN
			|| tokens[i].type == TOK_REDIR_OUT
			|| tokens[i].type == TOK_DREDIR_IN
			|| tokens[i].type == TOK_DREDIR_OUT)
			ret = check_redir_errors(tokens, i, count);
		else
			ret = 0;
		if (ret == -1)
			return (-1);
		i++;
	}
	return (0);
}
