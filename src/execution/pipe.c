/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:24:06 by tperes            #+#    #+#             */
/*   Updated: 2022/11/28 21:37:12 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	pipex(char *line)
{
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	fdout;
	int	i;
	char	**cmd;
	char	**cmd_args;
	int	fd_pipe[2];

	tmpin = dup(0);
	tmpout = dup(1);
	fdin = dup(tmpin);
	i = 0;
	cmd = ft_split(line, '|');
	while (cmd[i])
	{
		cmd_args = ft_split(cmd[i], ' ');
		dup2(fdin, 0);
		close(fdin);
		if (i == 2)
			fdout = dup(tmpout);
		else
		{
			pipe(fd_pipe);
			fdout = fd_pipe[1];
			fdin = fd_pipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		exec(cmd_args, cmd_args[0]);
		i++;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	return (0);
}
