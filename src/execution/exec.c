/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:29 by tperes            #+#    #+#             */
/*   Updated: 2023/01/12 17:30:35 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static void	exit_error(const char *format, const char *s, int code)
{
	printf(format, s);
	ft_lstclear(&g_minishell.envs, free_env);
	exit(code);
}

int	exec(char **av, char *cmd, int fd[2], int fd_in)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		reset_signals();
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(fd_in);
		if (cmd == NULL)
			exit_error("minishell: %s: command not found\n", av[0], 127);
		if (execve(cmd, av, list_to_tab(g_minishell.envs)) == -1)
			exit_error("minishell: %s: Permission denied\n", cmd, 126);
	}
	handle_signals_exec();
	close(fd[0]);
	close(fd[1]);
	return (pid);
}
