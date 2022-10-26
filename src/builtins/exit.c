/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:09:07 by tperes            #+#    #+#             */
/*   Updated: 2022/10/26 16:10:17 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

/*tests essayes

- exit
- exit 12
- exit 12 12 (trouver un bon main pour mieux tester les valeurs de retour)
- exit aa
- exit aa aa
- exit 0

*/

int	my_exit(int ac, char **av)
{
	int	status;

	printf("exit\n");
	status = 0;
	if (ac > 1)
	{
		if (ft_atoi(av[1]) == 0 && av[1][0] != '0')
		{
			printf("minishell: exit: %s: numeric argument required\n", av[1]);
			exit(2);
		}
		status = ft_atoi(av[1]);
	}
	if (ac > 2)
	{
		printf("minishell: too many arguments\n");
		return (1);
	}
	exit(status);
}

/*
int	main(int ac, char **av)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 5)
	{
		line = get_next_line(0);
		printf("%s", line);
		i++;
		free(line);
		my_exit(ac, av);
	}
	return (0);
}*/
