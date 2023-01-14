/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:29:02 by tperes            #+#    #+#             */
/*   Updated: 2023/01/13 13:11:32 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern t_minishell	g_minishell;

int	redir_file(t_command *cmd, int fdin)
{
	t_redirect	*redirect;
	t_list		*tmp_rd;

	tmp_rd = cmd->redirects;
	while (tmp_rd != NULL)
	{
		redirect = tmp_rd->content;
		if (redirect->type == RD_IN
			|| redirect->type == RD_HEREDOC)
		{
			fdin = dup(redirect->fd);
			if (fdin == -1)
				return (-1);
		}
		tmp_rd = tmp_rd->next;
	}
	return (fdin);
}

int	redir_input(int tpin, t_list *command)
{
	t_command	*cmd;
	int			fdin;

	fdin = dup(tpin);
	if (fdin == -1)
		return (-1);
	while (command != NULL)
	{
		cmd = command->content;
		fdin = redir_file(cmd, fdin);
		if (fdin == -1)
			return (-1);
		command = command->next;
	}
	return (fdin);
}

int	redir_output(int tpout, t_list *command)
{
	t_redirect	*redirect;
	t_command	*cmd;
	int			fdout;

	fdout = dup(tpout);
	if (fdout == -1)
		return (-1);
	while (command != NULL)
	{
		cmd = command->content;
		while (cmd->redirects != NULL)
		{
			redirect = cmd->redirects->content;
			dup2(redirect->fd, fdout);
			cmd->redirects = cmd->redirects->next;
		}
		command = command->next;
	}
	return (fdout);
}
