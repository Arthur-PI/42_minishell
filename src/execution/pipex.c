/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:27:51 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/21 12:25:32 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(int ac, char **av)
{
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
		fd_rw[1] = redir_output(fd_pipe[1], command);
	}
	else
		fd_rw[1] = redir_output(dup(STDOUT_FILENO), command);
	return (0);
}

int	forks(t_list *command, int fd_rw[2], int fd_pipe[2])
{
	t_command	*cmd;
	char		*tmp;
	int			last_pid;

	while (command)
	{
		cmd = command->content;
		handle_redirects(fd_rw, fd_pipe, command->next != NULL, command);
		if (!cmd->args)
			tmp = ft_strdup("");
		else
			tmp = file_to_execute(cmd->args[0]);
		last_pid = exec(cmd->args, tmp, fd_rw, fd_pipe[0]);
		free(tmp);
		command = command->next;
	}
	return (last_pid);
}

int	pipex(t_list *command)
{
	int			last_pid;
	int			fd_pipe[2];
	int			fd_rw[2];
	t_command	*cmd;

	last_pid = 0;
	fd_pipe[0] = dup(STDIN_FILENO);
	fd_pipe[1] = -1;
	cmd = command->content;
	if (cmd->args && command->next == NULL && ifbuiltins(cmd->args) == 0)
	{
		handle_redirects(fd_rw, fd_pipe, command->next != NULL, command);
		builtins_parent(nbr_args(cmd->args), cmd->args, fd_rw, fd_pipe[0]);
	}
	else
		last_pid = forks(command, fd_rw, fd_pipe);
	return (last_pid);
}
