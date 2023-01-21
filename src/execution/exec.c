/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:29 by tperes            #+#    #+#             */
/*   Updated: 2023/01/21 15:14:29 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static void	exit_error(const char *format, const char *s, int code, char *cmd)
{
	printf(format, s);
	ft_lstclear(&g_minishell.envs, free_env);
	ft_lstclear((t_list **)&g_minishell.commands, &free_command);
	if (cmd)
		free(cmd);
	exit(code);
}

void	piping(int fd[2], int fd_in)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (fd_in != -1)
		close(fd_in);
}

void	exec_or_error(char *cmd, char **av)
{
	char		**tab;
	struct stat	buf;

	if (cmd == NULL || ft_strlen(av[0]) == 0)
		exit_error("minishell: %s: command not found\n", av[0], 127, cmd);
	if (stat(cmd, &buf) != -1)
	{
		if (S_ISDIR(buf.st_mode))
			exit_error("minishell: %s: Is a directory\n", av[0], 126, cmd);
	}
	if (access(cmd, F_OK) == -1 && (ft_strncmp(av[0], "./", 2) == 0
			|| ft_strncmp(av[0], "../", 2) == 0
			|| ft_strncmp(av[0], "/", 1) == 0))
		exit_error("minishell: %s: No such file or directory\n",
			av[0], 127, cmd);
	if (builtins(nbr_args(av), av) == 0)
		ft_lstclear(&g_minishell.envs, free_env);
	else
	{
		tab = list_to_tab(g_minishell.envs);
		execve(cmd, av, tab);
		free_tab(tab);
		exit_error("minishell: %s: Permission denied\n", cmd, 126, cmd);
	}
}

void	quit_properly(char *s)
{
	free(s);
	ft_lstclear((t_list **)&g_minishell.commands, &free_command);
	ft_lstclear(&g_minishell.envs, &free_env);
	exit(g_minishell.exit_status);
}

int	exec(char **av, char *cmd, int fd[2], int fd_in)
{
	int			pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		reset_signals();
		if (fd[0] == -1 || fd[1] == -1)
			quit_properly(cmd);
		piping(fd, fd_in);
		exec_or_error(cmd, av);
		quit_properly(cmd);
	}
	handle_signals_exec();
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	return (pid);
}
