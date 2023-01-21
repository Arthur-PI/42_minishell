/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:24:06 by tperes            #+#    #+#             */
/*   Updated: 2023/01/21 12:17:05 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	save_std(int *tpin, int *tpout)
{
	*tpin = dup(STDIN_FILENO);
	*tpout = dup(STDOUT_FILENO);
}

void	reset_std(int tpin, int tpout)
{
	dup2(tpin, STDIN_FILENO);
	dup2(tpout, STDOUT_FILENO);
	close(tpin);
	close(tpout);
}

int	ifbuiltins(char **av)
{
	if (ft_strcmp(av[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(av[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(av[0], "env") == 0)
		return (0);
	else if (ft_strcmp(av[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(av[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(av[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(av[0], "export") == 0)
		return (0);
	else
		return (2);
}

int	builtins_parent(int ac, char **av, int fd[2], int fd_in)
{
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	piping(fd, fd_in);
	if (ft_strcmp(av[0], "cd") == 0)
		return (cd(ac, av));
	else if (ft_strcmp(av[0], "exit") == 0)
		return (my_exit(ac, av));
	else if (ft_strcmp(av[0], "env") == 0)
		return (my_env(ac, av));
	else if (ft_strcmp(av[0], "echo") == 0)
		return (echo(ac, av));
	else if (ft_strcmp(av[0], "pwd") == 0)
		return (pwd(ac));
	else if (ft_strcmp(av[0], "unset") == 0)
		return (my_unset(ac, av));
	else if (ft_strcmp(av[0], "export") == 0)
		return (my_export(ac, av));
	else
		return (2);
}

int	executing(t_list *command)
{
	int	tpin;
	int	tpout;
	int	last_pid;
	int	status;

	last_pid = 0;
	status = 0;
	save_std(&tpin, &tpout);
	last_pid = pipex(command);
	reset_std(tpin, tpout);
	if (last_pid == -1)
		return (-1);
	if (last_pid > 0)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status) && g_minishell.exit_status != 130
			&& last_pid != 0)
			g_minishell.exit_status = WEXITSTATUS(status);
	}
	while (wait(&status) != -1)
		continue ;
	handle_signals();
	return (0);
}
