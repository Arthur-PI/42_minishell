/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:29 by tperes            #+#    #+#             */
/*   Updated: 2022/12/30 05:32:53 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

int	exec(char **av, char *cmd)
{
	int	ret;

	ret = fork();
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		if (execve(cmd, av, NULL) == -1)
			perror("Error");
	}
	return (ret);
}
