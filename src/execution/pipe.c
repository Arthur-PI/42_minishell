/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:24:06 by tperes            #+#    #+#             */
/*   Updated: 2022/12/09 13:32:45 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	int	i;

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

t_command	*create_cmd(char *line, int j)
{
	t_command	*new_cmd;
	int			i;
	int			start;
	int			len;

	new_cmd = malloc(sizeof(*new_cmd));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (line[i])
		i++;
	new_cmd->cmd_full = line;
	len = len_cmd(line, j);
	start = start_cmd(line, j);
	new_cmd->cmd = ft_substr(line, start, len - start);
	new_cmd->args = ft_split(new_cmd->cmd, ' ');
	return (new_cmd);
}

t_list	*add_cmd(t_list *lst, char *line, int i)
{
	t_list	*new;
	t_command	*command;

	command = create_cmd(line, i);
	new = ft_lstnew(command);
	ft_lstadd_back(&lst, new);
	if (command == NULL || new == NULL)
	{
		free_cmd(command);
		ft_lstclear(&lst, &free_cmd);
		exit(1);
	}
	return (lst);
}

//pas sure du return(1) => a revoir
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
		return (1);
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

int	pipex(char *line)
{
	int	tpin;
	int	tpout;
	int	fdin;
	int	fdout;
	t_command	*command;
	t_list	*cmd;
	int	fd_pipe[2];

	tpin = dup(0);
	tpout = dup(1);
	fdin = redir_input(tpin);
	if (fdin == -1)
		return (0);
	cmd = list_cmd(line);
	while (cmd != NULL)
	{
		command = cmd->content;
		dup2(fdin, 0);
		close(fdin);
		if (cmd->next == NULL)
			fdout = dup(tpout);
		else
		{
			pipe(fd_pipe);
			fdout = fd_pipe[1];
			fdin = fd_pipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		if (builtins(nbr_args(command->args), command->args) == 1)
			exec(command->args, get_path_cmd(command->args[0]));
		cmd = cmd->next;
	}
	return (dup2(tpin, 0), dup2(tpout, 1), close(tpin), close(tpout), 0);
}
