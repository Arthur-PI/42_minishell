/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:29 by tperes            #+#    #+#             */
/*   Updated: 2023/01/12 17:30:35 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

extern t_minishell	g_minishell;

int	exec(char **av, char *cmd)
{
	int	ret;

	ret = fork();
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		if (execve(cmd, av, NULL) == -1)
		{
			printf("%s: command not found\n", av[0]);
			ft_lstclear(&g_minishell.envs, free_env);
			exit(127);
		}
	}
	return (ret);
}
