/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:23:23 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/11 15:20:21 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_redirects(t_list *redirects)
{
	t_redirect	*redirect;

	printf("{");
	while (redirects)
	{
		redirect = redirects->content;
		printf("%s: %d", redirect->file, redirect->fd);
		if (redirects->next)
			printf(", ");
		redirects = redirects->next;
	}
	printf("}");
}

static void	print_command(t_command *command)
{
	int		i;
	char	*s;
	char	*tmp;

	i = 0;
	s = ft_strdup("");
	while (command->args && command->args[i])
	{
		tmp = s;
		s = ft_strjoin(s, command->args[i]);
		free(tmp);
		tmp = s;
		s = ft_strjoin(s, " ");
		free(tmp);
		i++;
	}
	printf("Command -> (%s) (rd = ", s);
	print_redirects(command->redirects);
	printf(")\n");
	free(s);
}

void	print_commands(t_list *commands)
{
	t_command	*cmd;

	while (commands)
	{
		cmd = commands->content;
		print_command(cmd);
		commands = commands->next;
	}
}

static void	free_redirect(void *ptr)
{
	t_redirect	*rd;

	rd = ptr;
	if (rd)
	{
		free(rd->file);
		if (rd->fd != 1 && rd->fd != -1)
			close(rd->fd);
		free(rd);
	}
}

void	free_command(void *ptr)
{
	int			i;
	t_command	*cmd;

	cmd = ptr;
	if (cmd)
	{
		i = 0;
		free(cmd->cmd);
		while (cmd->args && cmd->args[i])
			free(cmd->args[i++]);
		if (cmd->args)
			free(cmd->args);
		ft_lstclear(&cmd->redirects, &free_redirect);
		free(cmd);
	}
}
