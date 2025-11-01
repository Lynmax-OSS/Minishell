/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4b_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrajendr <qrajendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:59:50 by qrajendr          #+#    #+#             */
/*   Updated: 2025/11/02 01:09:57 by qrajendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_child_signal(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	exit(130);
}

static void	heredoc_child_process(int write_fd, char *delimiter, t_env *env)
{
	char	*line;
	char	*expanded_line;

	signal(SIGINT, heredoc_child_signal);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
			ft_putstr_fd("delimited by end-of-file\n", STDERR_FILENO);
			exit(0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			exit(0);
		}
		expanded_line = expand_heredoc_line(line, env);
		write(write_fd, expanded_line, ft_strlen(expanded_line));
		write(write_fd, "\n", 1);
		free(expanded_line);
		free(line);
	}
}

static int	create_heredoc_process(char *delimiter, t_env *env, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(pipe_fd[0]);
		heredoc_child_process(pipe_fd[1], delimiter, env);
	}
	return (pid);
}

static int	heredoc_wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
			return (-1);
		return (0);
	}
	return (-1);
}

int	create_heredoc(char *delimiter, t_env *env)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		result;

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	pid = create_heredoc_process(delimiter, env, pipe_fd);
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	close(pipe_fd[1]);
	result = heredoc_wait_for_child(pid);
	if (result == -1)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}
