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

void	ft_putstr_fd1(const char *s, int fd)
{
	if (s)
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
	}
}

static void	heredoc_readlines(char *stop, int fd)
{
	char	*line;
	char	*line_expand;

	line = readline("> ");
	while (line && ft_strcmp(line, stop) != 0)
	{
		line_expand = replace_envs(line);
		ft_putendl_fd(line_expand, fd);
		free(line_expand);
		line = readline("> ");
	}
	if (line)
		free(line);
}

int	handle_heredoc(char *stop)
{
	int		fd[2];
	int		stdin_clone;

	if (pipe(fd) == -1)
		return (-1);
	stdin_clone = dup(STDIN_FILENO);
	handle_signals_heredoc();
	heredoc_readlines(stop, fd[1]);
	close(fd[1]);
	if (g_minishell.signal == 1)
	{
		close(fd[0]);
		dup2(stdin_clone, STDIN_FILENO);
		g_minishell.exit_status = 130;
		fd[0] = -1;
	}
	close(stdin_clone);
	handle_signals();
	return (fd[0]);
}
