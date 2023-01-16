/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:29 by tperes            #+#    #+#             */
/*   Updated: 2023/01/16 17:58:03 by tperes           ###   ########.fr       */
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

int	exec(char **a, char *cmd)
{
	int	ret;
	struct stat	buf;

	ret = fork();
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		if (cmd == NULL)
			exit_error("minishell: %s: command not found\n", a[0], 127);
		if (stat(cmd, &buf) != -1)
		{
			if (S_ISDIR(buf.st_mode))
				exit_error("minishell: %s: Is a directory\n", a[0], 126);
		}
		if (access(cmd, F_OK) == -1 && (ft_strncmp(a[0], "./", 2) == 0
				|| ft_strncmp(a[0], "../", 2) == 0
				|| ft_strncmp(a[0], "/", 1) == 0))
			exit_error("minishell: %s: No such file or directory\n", a[0], 127);
		else if (execve(cmd, a, NULL) == -1)
			exit_error("minishell: %s: Permission denied\n", cmd, 126);
	}
	return (ret);
}
