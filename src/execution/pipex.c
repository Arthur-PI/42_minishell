/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:27:51 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/17 13:42:57 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

int	handle_redirects(int fd_rw[2], int fd_pipe[2], int next, t_list *command)
{
	fd_rw[0] = redir_input(fd_pipe[0], command);
	if (next)
	{
		if (pipe(fd_pipe) == -1)
			return (-1);
		fd_rw[1] = fd_pipe[1];
	}
	else
		fd_rw[1] = redir_output(dup(STDOUT_FILENO), command);
	return (0);
}

// TODO FIX handle pipe return value in case of error (-1)
int	pipex(t_list *command)
{
	int			last_pid;
	int			fd_pipe[2];
	int			fd_rw[2];
	char		*tmp;
	t_command	*cmd;

	last_pid = 0;
	fd_pipe[0] = dup(STDIN_FILENO);
	fd_pipe[1] = -1;
	while (command)
	{
		cmd = command->content;
		handle_redirects(fd_rw, fd_pipe, command->next != NULL, command);
		if (builtins(nbr_args(cmd->args), cmd->args) == 2)
		{
			tmp = get_path_cmd(cmd->args[0]);
			last_pid = exec(cmd->args, tmp, fd_rw, fd_pipe[0]);
			free(tmp);
		}
		else
			last_pid = 0;
		command = command->next;
	}
	return (last_pid);
}