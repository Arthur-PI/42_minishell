/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:42:55 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/05 21:42:57 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	*create_command(t_token *token)
{
	t_command	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		exit(12);
	cmd->cmd = NULL;
	if (token)
	{
		cmd->cmd = ft_strdup(token->value);
		if (!cmd->cmd)
			exit(12);
	}
	cmd->args = NULL;
	cmd->redirects = NULL;
	return (cmd);
}
