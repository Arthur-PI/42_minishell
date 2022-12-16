/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:24:06 by tperes            #+#    #+#             */
/*   Updated: 2022/12/16 10:57:02 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"
#include <errno.h>

extern t_minishell	g_minishell;

char	*get_path_cmd(char *cmd)
{
	t_env	*env;
	t_list	*lst;
	char	**path;
	int		i;

	env = NULL;
	lst = g_minishell.envs;
	while (lst != NULL)
	{
		env = lst->content;
		if (env == get_env_el("PATH"))
			break ;
		lst = lst->next;
	}
	path = ft_split(env->value, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		if (access(ft_strjoin(path[i], cmd), F_OK) == 0)
			return (ft_strjoin(path[i], cmd));
		i++;
	}
	return (NULL);
}

int	builtins(int ac, char **av)
{
	if (ft_strcmp(av[0], "echo") == 0)
		return (echo(ac, av));
	else if (ft_strcmp(av[0], "cd") == 0)
		return (printf("my cd\n"), cd(ac, av));
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
int	pipex(int fdin, int tpout, int ret, t_list *command)
{
	t_command	*cmd;
	int			fdout;
	int			fd_pipe[2];

	while (command != NULL)
	{

		cmd = command->content;
		dup2(fdin, 0);
		close(fdin);
		if (command->next == NULL)
			fdout = redir_output(tpout, fdin, command);
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
			ret = exec(cmd->args, get_path_cmd(cmd->args[0]));
		command = command->next;
	}
	return (ret);
}

int	executing(t_list *command)
{
	int	tpin;
	int	tpout;
	int	fdin;
	int	ret;

	tpin = dup(0);
	ret = 0;
	tpout = dup(1);
	fdin = redir_input(tpin, command);
	if (fdin == -1)
		return (0);
	ret = pipex(fdin, tpout, ret, command);
	if (ret != 0)
		waitpid(ret, NULL, 0);
	return (dup2(tpin, 0), dup2(tpout, 1), close(tpin), close(tpout), 0);
}
