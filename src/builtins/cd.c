/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:47:15 by tperes            #+#    #+#             */
/*   Updated: 2022/11/01 17:16:29 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
- cd with a directory that exists
- cd with a directory that doesn't exist
- cd with many arguments
TODO cd with no argument
*/

int	cd(int ac, char **av)
{
	if (ac > 2)
		return (printf("cd: string not in pwd: %s\n", av[1]), 1);
	if (chdir(av[1]) == -1)
		return (printf("cd: no such file or directory: %s\n", av[1]), 1);
	return (0);
}
