/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:24:06 by tperes            #+#    #+#             */
/*   Updated: 2023/01/14 15:51:20 by tperes           ###   ########.fr       */
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
		if (WIFEXITED(status) && g_minishell.exit_status != 130)
			g_minishell.exit_status = WEXITSTATUS(status);
	}
	while (wait(&status) != -1)
		continue ;
	handle_signals();
	return (0);
}
