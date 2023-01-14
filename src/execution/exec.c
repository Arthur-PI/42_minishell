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

extern t_minishell	g_minishell;

static void	exit_error(const char *format, const char *s, int code)
{
	printf(format, s);
	ft_lstclear(&g_minishell.envs, free_env);
	exit(code);
}

int	exec(char **av, char *cmd)
{
	int	ret;

	ret = fork();
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		if (cmd == NULL)
			exit_error("minishell: %s: command not found\n", av[0], 127);
		if (execve(cmd, av, NULL) == -1)
			exit_error("minishell: %s: Permission denied\n", cmd, 126);
	}
	return (ret);
}
