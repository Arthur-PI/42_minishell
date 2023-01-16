/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:24:06 by tperes            #+#    #+#             */
/*   Updated: 2023/01/16 16:33:36 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parser.h"
#include <errno.h>

extern t_minishell	g_minishell;

int	builtins(int ac, char **av)
{
	if (ft_strcmp(av[0], "echo") == 0)
		return (echo(ac, av));
	else if (ft_strcmp(av[0], "cd") == 0)
		return (cd(ac, av));
	else if (ft_strcmp(av[0], "exit") == 0)
		return (my_exit(ac, av));
	else if (ft_strcmp(av[0], "pwd") == 0)
		return (pwd(ac));
	else if (ft_strcmp(av[0], "env") == 0)
		return (my_env(ac, av));
	else if (ft_strcmp(av[0], "unset") == 0)
		return (my_unset(ac, av));
	else if (ft_strcmp(av[0], "export") == 0)
		return (my_export(ac, av));
	else
		return (2);
}

int	nbr_args(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

// TODO FIX handle pipe return value in case of error (-1)
int	pipex(int fdin, int tpout, t_list *command)
{
	t_command	*cmd;
	int			fdout;
	int			fd_pipe[2];
	char		*tmp;

	while (command != NULL)
	{
		cmd = command->content;
		fdin = redir_input(fdin, command);
		if (fdin == -1)
			return (-1);
		dup2(fdin, 0);
		close(fdin);
		if (command->next == NULL)
			fdout = redir_output(tpout, command);
		else
		{
			if (pipe(fd_pipe) == -1)
				return (-1);
			fdout = fd_pipe[1];
			fdin = fd_pipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		if (builtins(nbr_args(cmd->args), cmd->args) == 2)
		{
			tmp = get_path_cmd(cmd->args[0]);
			cmd->pid = exec(cmd->args, tmp);
			free(tmp);
		}
		else
			cmd->pid = 0;
		command = command->next;
	}
	return (cmd->pid);
}

void	killing_processes(t_list *command)
{
	t_command	*cmd;

	while (command->next != NULL)
	{
		cmd = command->content;
		kill(cmd->pid, SIGKILL);
		command = command->next;
	}
}

int	executing(t_list *command)
{
	int	tpin;
	int	tpout;
	int	ret;
	int	status;

	tpin = dup(0);
	ret = 0;
	status = 0;
	tpout = dup(1);
	ret = pipex(tpin, tpout, command);
	if (ret == -1)
		return (-1);
	if (ret > 0)
		waitpid(ret, &status, 0);
	killing_processes(command);
	if (WIFEXITED(status) && g_minishell.exit_status != 130 && ret != 0)
		g_minishell.exit_status = WEXITSTATUS(status);
	return (dup2(tpin, 0), dup2(tpout, 1), close(tpin), close(tpout), 0);
}
