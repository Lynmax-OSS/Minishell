/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4a_single_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:18:41 by qrajendr          #+#    #+#             */
/*   Updated: 2025/11/02 01:26:36 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
	}
	return (fd);
}

static int	open_output_file(char *filename, int is_append)
{
	int	flags;
	int	fd;

	if (is_append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
	}
	return (fd);
}

static int	apply_input_redirection(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	apply_output_redirection(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_single_redirection(t_redir *redir, t_env *env)
{
	int	fd;

	fd = -1;
	if (ft_strcmp(redir->type, "<") == 0)
		fd = open_input_file(redir->target);
	else if (ft_strcmp(redir->type, ">") == 0)
		fd = open_output_file(redir->target, 0);
	else if (ft_strcmp(redir->type, ">>") == 0)
		fd = open_output_file(redir->target, 1);
	else if (ft_strcmp(redir->type, "<<") == 0)
	{
		if (redir->fd != -1)
		{
			fd = redir->fd;
			/* consume the stored fd so child doesn't try to reuse it */
			redir->fd = -1;
		}
		else
			fd = create_heredoc(redir->target, env);
	}
	if (fd == -1)
		return (1);
	if (ft_strcmp(redir->type, "<") == 0 || ft_strcmp(redir->type, "<<") == 0)
		return (apply_input_redirection(fd));
	else
		return (apply_output_redirection(fd));
}
