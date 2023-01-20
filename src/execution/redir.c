/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:29:02 by tperes            #+#    #+#             */
/*   Updated: 2023/01/18 19:27:17 by tperes           ###   ########.fr       */
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

int	redir_input(int fdin, t_list *command)
{
	t_command	*cmd;

	if (fdin == -1)
		return (-1);
	cmd = command->content;
	fdin = redir_file(cmd, fdin);
	if (fdin == -1)
		return (-1);
	return (fdin);
}

int	redir_output(int fdout, t_list *command)
{
	t_redirect	*redirect;
	t_command	*cmd;

	if (fdout == -1)
		return (-1);
	cmd = command->content;
	while (cmd->redirects != NULL)
	{
		redirect = cmd->redirects->content;
		if (redirect->type == RD_OUT || redirect->type == RD_APPEND)
			dup2(redirect->fd, fdout);
		cmd->redirects = cmd->redirects->next;
	}
	return (fdout);
}
