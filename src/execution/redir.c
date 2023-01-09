/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:29:02 by tperes            #+#    #+#             */
/*   Updated: 2023/01/09 14:50:04 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	redir_input(int tpin, t_list *command)
{
	t_command	*cmd;
	t_list		*tmp_command;
	t_list		*tmp_rd;
	t_redirect	*redirect;
	int			fdin;

	fdin = dup(tpin);
	tmp_command = command;
	while (tmp_command != NULL)
	{
		cmd = tmp_command->content;
		tmp_rd = cmd->redirects;
		while (tmp_rd != NULL)
		{
			redirect = tmp_rd->content;
			if (redirect->type == RD_IN)
			{
				printf("%s\n", redirect->file);
				fdin = dup(redirect->fd);
			}
			tmp_rd = tmp_rd->next;
		}
		tmp_command = tmp_command->next;
	}
	return (fdin);
}

int	redir_output(int tpout, t_list *command)
{
	t_redirect	*redirect;
	t_command	*cmd;
	int			fdout;

	fdout = dup(tpout);
	while (command != NULL)
	{
		cmd = command->content;
		while (cmd->redirects != NULL)
		{
			redirect = cmd->redirects->content;
			if (redirect->type == RD_OUT)
				fdout = open(redirect->file, O_WRONLY);
			cmd->redirects = cmd->redirects->next;
		}
		command = command->next;
	}
	return (fdout);
}
