/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:24:06 by tperes            #+#    #+#             */
/*   Updated: 2022/12/07 16:10:10 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "builtins.h"

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

//au lieu d'utiliser split => utiliser t_token_type?
// utiliser la structure de commandes 
int	pipex(char *line)
{
	int	tpin;
	int	tpout;
	int	fdin;
	int	fdout;
	int	i;
	char	**cmd;
	char	**cmd_args;
	int	fd_pipe[2];

	tpin = dup(0);
	tpout = dup(1);
	fdin = redir_input(tpin);
	if (fdin == -1)
		return (0);
	i = 0;
	cmd = ft_split(line, '|');
	while (cmd[i])
	{
		cmd_args = ft_split(cmd[i], ' ');
		dup2(fdin, 0);
		close(fdin);
		if (i == 0)
			fdout = dup(tpout);
		else
		{
			pipe(fd_pipe);
			fdout = fd_pipe[1];
			fdin = fd_pipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
	//	if (cmd_args[0] == builtin(cmd_args[0]))
	//		exec_builtin(ac, av, env);
	//	else
		exec(cmd_args, get_path_cmd(cmd_args[0]));
		i++;
	}
	return (dup2(tpin, 0), dup2(tpout, 1), close(tpin), close(tpout), 0);
}
