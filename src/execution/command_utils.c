/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:49:56 by tperes            #+#    #+#             */
/*   Updated: 2022/12/08 18:17:14 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "builtins.h"
#include "parser.h"

int	nbr_pipes(char *line, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == c)
			j++;
		i++;
	}
	return (j);
}

int	start_cmd(char *line, int j)
{
	int	i;
	int	k;
	int	cmd;

	k = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (k == j)
			{
				if (k == 0)
					cmd = 0;
				else
					cmd = ft_strlen(line) - i;
				break ;
			}
			cmd = i + 1;
			k++;
		}
		i++;
	}
	return (cmd);
}

int	len_cmd(char *line, int j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (k == j)
				return (i);
			k++;
		}
		i++;
	}
	return (i);
}

void	free_cmd(void *ptr)
{
	t_command	*cmd;

	cmd = ptr;
	if (cmd)
	{
		free(cmd->cmd);
		free(cmd->args);
		free(cmd->cmd_full);
		free(cmd);
	}
}

t_list	*list_cmd( char *line)
{
	int		i;
	t_list	*lst_cmd;

	i = 0;
	lst_cmd = NULL;
	while (i <= nbr_pipes(line, '|'))
	{
		lst_cmd = add_cmd(lst_cmd, line, i);
		i++;
	}
	return (lst_cmd);
}
