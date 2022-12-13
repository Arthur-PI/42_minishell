/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:24:06 by tperes            #+#    #+#             */
/*   Updated: 2022/12/13 18:14:12 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

extern t_minishell	g_minishell;

int	redir_input(int tmpin)
{
	int		fdin;
//	t_redirect	*redirect;

//	if (redirect.file)
//		fdin = open(redirect.file, O_RDONLY);
//	else
	fdin = dup(tmpin);
	return (fdin);
}

char	*get_path_cmd(char *cmd)
{
	t_env	*env;
	t_list	*lst;
	char	**path;
	int		i;

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

/*int	redir_output(int fdout)
{
	int		tmpout;
	t_redirect	*redirect;
	char		*new_file;

	tmpout = dup(0);
	new_file = cmd_args;
	if (redirect.file)
		fdout = open(redirect.file, O_TRUNC)
	else
		fdout = open(new_file, O_CREAT | O_WRONLY);
	return (fdout);
}*/

int	pipex(int fdin, int tpout, int ret, t_list *command)
{
	int	fdout;
	int	fd_pipe[2];
	t_command	*cmd;

	while (command != NULL)
	{
		cmd = command->content;
		dup2(fdin, 0);
		close(fdin);
		if (command->next == NULL)
			fdout = dup(tpout);
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
	fdin = redir_input(tpin);
	if (fdin == -1)
		return (0);
	ret = pipex(fdin, tpout, ret, command);
	if (ret != 0)
		waitpid(ret, NULL, 0);
	return (dup2(tpin, 0), dup2(tpout, 1), close(tpin), close(tpout), 0);
}
