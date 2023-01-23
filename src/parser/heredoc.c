/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:20:49 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/14 15:52:21 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static void	heredoc_readlines(const char *stop, int fd)
{
	char	*line;
	char	*line_expand;

	line = readinput("> ");
	while (line && ft_strcmp(line, stop) != 0)
	{
		line_expand = replace_envs(line);
		ft_putendl_fd(line_expand, fd);
		free(line_expand);
		line = readinput("> ");
	}
	if (line)
		free(line);
}

static int	handle_heredoc_notty(const char *stop)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	heredoc_readlines(stop, fd[1]);
	close(fd[1]);
	return (fd[0]);
}

static int	handle_heredoc_fork(const char *stop)
{
	int		fd[2];
	int		pid;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (!pid)
	{
		reset_signals();
		close(fd[0]);
		heredoc_readlines(stop, fd[1]);
		close(fd[1]);
		exit(0);
	}
	handle_signals_heredoc();
	close(fd[1]);
	wait(&status);
	handle_signals();
	if (status == SIGINT)
		return (close(fd[0]), -1);
	return (fd[0]);
}

int	handle_heredoc(const char *stop)
{
	if (!isatty(STDIN_FILENO))
		return (handle_heredoc_notty(stop));
	return (handle_heredoc_fork(stop));
}
