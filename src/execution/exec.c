/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:29 by tperes            #+#    #+#             */
/*   Updated: 2023/01/20 10:51:31 by tperes           ###   ########.fr       */
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
	int			pid;
	struct stat	buf;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		reset_signals();
		piping(fd, fd_in);
		if (cmd == NULL)
			exit_error("minishell: %s: command not found\n", av[0], 127);
		if (stat(cmd, &buf) != -1)
		{
			if (S_ISDIR(buf.st_mode))
				exit_error("minishell: %s: Is a directory\n", av[0], 126);
		}
		if (access(cmd, F_OK) == -1 && (ft_strncmp(av[0], "./", 2) == 0
				|| ft_strncmp(av[0], "../", 2) == 0
				|| ft_strncmp(av[0], "/", 1) == 0))
			exit_error("minishell: %s: No such file or directory\n", av[0], 127);
		if (ft_strcmp(av[0], "echo") == 0)
			echo(nbr_args(av), av);
		else if (ft_strcmp(av[0], "env") == 0)
			my_env(nbr_args(av), av);
		else if (execve(cmd, av, NULL) == -1)
			exit_error("minishell: %s: Permission denied\n", cmd, 126);
	}
	handle_signals_exec();
	close(fd[0]);
	close(fd[1]);
	return (pid);
}
